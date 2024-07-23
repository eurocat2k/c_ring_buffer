#include "ast2lr.h"
#include "geom.h"
#include "hexdump.h"
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma scalar_storage_order default

struct trk_status_t {
    union {
        uint8_t octets[MAX_STATUS_OCTETS];
        // 1st octet
        struct {
            // 1st octet
            uint8_t fx1 : 1; // LSB
            uint8_t cnf : 1;
            uint8_t src : 3;
            uint8_t mrh : 1;
            uint8_t spi : 1;
            uint8_t mon : 1; // MSB
            // 2nd octet: AKA 1st extent
            uint8_t fx2 : 1; // LSB
            uint8_t kos : 1;
            uint8_t stp : 1;
            uint8_t aff : 1;
            uint8_t fpc : 1;
            uint8_t tsb : 1;
            uint8_t tse : 1;
            uint8_t sim : 1; // MSB
            // 3rd octet: AKA 2nd extent
            uint8_t fx3 : 1; // LSB
            uint8_t md5 : 2;
            uint8_t mi  : 1;
            uint8_t me  : 1;
            uint8_t md4 : 2;
            uint8_t ama : 1; // MSB
            // 4th octet: AKA 3rd extent
            uint8_t fx4 : 1; // LSB
            uint8_t aac : 1;
            uint8_t suc : 1;
            uint8_t ads : 1;
            uint8_t mds : 1;
            uint8_t ssr : 1;
            uint8_t psr : 1;
            uint8_t cst : 1; // MSB
            // 5th octet: AKA 4th extent
            uint8_t fx5  : 1; // LSB
            uint8_t fplt : 1;
            uint8_t pft : 1;
            uint8_t ems : 3;
            uint8_t sds : 2; // MSB
        } __attribute__((packed)) bf1;
        //
    } status;
} __attribute__((packed));


struct mode3a_t {
    union {
        uint16_t short_value;
        uint8_t octets[MAX_MODE3A_OCTETS];
        struct {
            uint16_t d : 3; // LSB
            uint16_t c : 3;
            uint16_t b : 3;
            uint16_t a : 3;
            uint16_t sp : 1;
            uint16_t ch : 1;
            uint16_t g : 1;
            uint16_t v : 1; // MSB
        } bf;
    } mod3a;
} __attribute__ ((packed));

struct ast_to_lr_t {
    uint8_t callsign[CALLSIGN_LENGTH];
    uint8_t adep[DEP_LENGTH];
    uint8_t ades[DES_LENGTH];
    uint8_t atyp[ATYP_LENGTH];
    uint8_t wtc[WTC_LENGTH];
    uint8_t icaoaddr[MAX_ICAO_ADDR_LENGTH];
    uint16_t trknum;
    // uint16_t mode3a;
    mode3a_t squawk;
    double x;
    double y;
    double dx;
    double dy;
    uint16_t mfl;
    uint16_t balt;
    attitude_t att;
    struct trk_status_t status;
};

uint16_t MatXY_To_LRXY(double v) {
    uint16_t ret = 0;
    const double coef = pow(2.0, -6.0);
    // const double coef = 1.0 / 64.0;
    double tmp = 0.0, val = 0.0, aval = fabs(v) * M_TO_NM;
    uint16_t mask = 0x4000;
    printf("coef = %f, v = %f\n", coef, v);
    for (double i = 14.0; i > 0.0; i -= 1.0) {
        tmp = pow(2.0, i) * coef;
        if ((val + tmp) <= aval)
        {
            ret |= mask;
            val += tmp;
        }
        printf("tmp = %f, val = %f, aval = %f [%04x]\n", tmp, val, aval, ret);
        mask >>= 1;
    }
    if (v < 0.0) {
        ret = ~ret;
        ret += 1;
    }
    printf("!!tmp = %f, val = %f, aval = %f [%04x]!!\n", tmp, val, aval, ret);
    return ret;
}

uint16_t MatDXY_To_LRDXY(double v) {
    uint16_t ret = 0;
    const double coef = pow(2.0, -22.0) / pow(10.0, -2.0);
    double nmps = v * MPS_TO_NMPS, anmps = fabs(v * MPS_TO_NMPS), val = 0.0, tmp = 0.0;
    uint16_t mask = 4000;
    printf("v = %f, nmps = %f, anmps = %f\n", v, nmps, anmps);
    for (double i = 14.0; i >= 0; i -= 1.0) {
        tmp = pow(2.0, i) * coef;
        if (anmps >= (val + tmp)) {
            ret |= mask;
            val += tmp;
        }
        mask >>= 1;
    }
    if (v < 0.0) {
        ret = ~ret;
        ret += 1;
    }
    return ret;
}

uint16_t MatLVL_ToLRLVL(uint16_t mfl) {
    uint16_t ret = 0;
    printf("%04x (%u)\n", mfl, mfl);
    double fl = (double)mfl * pow(2.0, -2.0);
    printf("fl = %f, mfl = %u\n", fl, (mfl >> 2));
    ret = mfl >> 2;
    return ret;
}

int Convert_ASTCAT62_TO_LRTGT(const void *sdata, void *dst) {
    char *ptr = (char *)dst;
    size_t max = MAX_LR_MSG_LENGTH, len = 0, offset = 0;
    ast_to_lr_t *ast = (ast_to_lr_t *)sdata;
    // we presume that all CAT62 track is enroute track
    // the first two character of the LR record is the target record identifier
    // which takes two characters and the default value is '42' or '82'
    offset += (size_t)snprintf((char *)(ptr + offset), strlen("82") + 1, "82");
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put tracknum 5 characters long - padded with leading zeroes
    offset += (size_t)snprintf((char *)(ptr + offset), 5+1, "%05u", ast->trknum);
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put X value calling MatXY_To_LRXY function on X
    offset += (size_t)snprintf((ptr + offset), 5 + 1, "%05u", MatXY_To_LRXY(ast->x));
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put Y value calling MatXY_To_LRXY function on X
    offset += (size_t)snprintf((ptr + offset), 5 + 1, "%05u", MatXY_To_LRXY(ast->y));
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put DX value calling MatXY_To_LRDXY function on X
    offset += (size_t)snprintf((ptr + offset), 5 + 1, "%05u", MatDXY_To_LRDXY(ast->dx));
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put DY value calling MatXY_To_LRDXY function on X
    offset += (size_t)snprintf((ptr + offset), 5 + 1, "%05u", MatDXY_To_LRDXY(ast->dy));
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put LVL value calling MatLVL_To_LRLVL function on X
    offset += (size_t)snprintf((ptr + offset), 3 + 1, "%03d", MatLVL_ToLRLVL(ast->mfl));
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put out squawk
    // offset += (size_t)snprintf((ptr + offset), (4) + 1, "%04o", ast->squawk.mod3a.short_value & 0x0FFF);
    offset += (size_t)snprintf((ptr + offset), (4) + 1, "%0o%0o%0o%0o",
                               ast->squawk.mod3a.bf.a, ast->squawk.mod3a.bf.b,
                               ast->squawk.mod3a.bf.c, ast->squawk.mod3a.bf.d);
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put ps low
    offset += (size_t)snprintf((ptr + offset), (2) + 1, "%02d", 0);
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put ps high
    offset += (size_t)snprintf((ptr + offset), (2) + 1, "%02d", 0);
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put callsign with fixed length
    offset += (size_t)snprintf((ptr + offset), CALLSIGN_LENGTH + 1, "%-8s", ast->callsign);
    // enroute or arrival or departire?
    if (memcmp((const char *)ast->adep, (const char *)ast->ades, DEP_LENGTH) == 0) {
        if (memcmp((const char *)ast->ades, "LHBP", DEP_LENGTH) == 0) {
            // presumably arrival
            offset += (size_t)snprintf((ptr + offset), DES_LENGTH + 1, "%c", 'A');
        }
    } else {
        if (memcmp((const char *)ast->ades, "LHBP", DEP_LENGTH) == 0) {
            // presumably arrival
            offset +=
                (size_t)snprintf((ptr + offset), DES_LENGTH + 1, "%c", 'A');
        } else if (memcmp((const char *)ast->adep, "LHBP", DEP_LENGTH) == 0) {
            // presumably arrival
            offset +=
                (size_t)snprintf((ptr + offset), DES_LENGTH + 1, "%c", 'D');
        } else {
            // presumably enriute
            offset +=
                (size_t)snprintf((ptr + offset), DES_LENGTH + 1, "%c", '_');
        }
    }
    // put a space
    offset += (size_t)snprintf((char *)(ptr + offset), strlen(" ") + 1, " ");
    // put icao address if any
    offset += (size_t)snprintf((ptr + offset), (2 * 3) + 1, "%06X",
                               ((ast->icaoaddr[0] << 16) |
                                (ast->icaoaddr[1] << 8) | ast->icaoaddr[2]));
    // put closing CR + LF
    offset += (size_t)snprintf((ptr + offset), 2 + 1, "%c%c", 0x0a, 0x0d);
    return (max - offset);
}

int Convert_ASTCAT65_TO_LRNS(const void *sdata, void *dst) { return 0; }

// TEST BITFIELDS

int main(void) {
    uint8_t buf[MAX_LR_MSG_LENGTH + 1] = {0};
    ast_to_lr_t ast = {0};
    trk_status_t st;
    for (int i = 0; i < MAX_STATUS_OCTETS; i += 1) {
        st.status.octets[i] = 0;
    }
    // fill trk status data
    st.status.octets[0] = 0xD5;
    st.status.octets[1] = 0xD5;
    st.status.octets[2] = 0xD5;
    st.status.octets[3] = 0xD5;
    st.status.octets[4] = 0xA5;
    // status
    ast.status = st;
    // fill callsign
    snprintf((char *)&ast.callsign[0], CALLSIGN_LENGTH+1, "MAH610");
    // fill adep
    snprintf((char *)&ast.adep, DEP_LENGTH+1, "LHBP");
    // fill ades
    snprintf((char *)&ast.ades, DEP_LENGTH+1, "EGGK");
    // fill atyp
    snprintf((char *)&ast.atyp, ATYP_LENGTH+1, "B733");
    // fill wtc
    snprintf((char *)&ast.wtc, WTC_LENGTH+1, "M");
    // trknum
    ast.trknum = 0x0175;
    // icao address
    ast.icaoaddr[0] = 0x47;
    ast.icaoaddr[1] = 0x21;
    ast.icaoaddr[2] = 0x04;
    // modeC
    ast.squawk.mod3a.short_value = 0x16b7;
    // mfl
    ast.mfl = 0x0582;
    // x
    ast.x = 15688.5;
    // y
    ast.y = -80182.5;
    // dx
    ast.dx = 219.9;
    // dy
    ast.dy = -85.5;
    // Call convert TGT message
    Convert_ASTCAT62_TO_LRTGT(&ast, &buf);
    // print out LR record
    HexDump(buf, strlen((const char *)&buf));
    //
    printf("%s\n", buf);
    // printf("[ 1 1 0 1 0 1 0 1 ]\n");
    // printf("mon = %d\n", st.status.bf1.mon);
    // printf("spi = %d\n", st.status.bf1.spi);
    // printf("mrh = %d\n", st.status.bf1.mrh);
    // printf("src = %d\n", st.status.bf1.src);
    // printf("cnf = %d\n", st.status.bf1.cnf);
    // printf(" fx = %d\n\n", st.status.bf1.fx1);
    // printf("[ 1 1 0 1 0 1 0 1 ]\n");
    // printf("sim = %d\n", st.status.bf1.sim);
    // printf("tse = %d\n", st.status.bf1.tse);
    // printf("tsb = %d\n", st.status.bf1.tsb);
    // printf("fpc = %d\n", st.status.bf1.fpc);
    // printf("aff = %d\n", st.status.bf1.aff);
    // printf("stp = %d\n", st.status.bf1.stp);
    // printf("kos = %d\n", st.status.bf1.kos);
    // printf(" fx = %d\n\n", st.status.bf1.fx2);
    // printf("[ 1 1 0 1 0 1 0 1 ]\n");
    // printf("ama = %d\n", st.status.bf1.ama);
    // printf("md4 = %d\n", st.status.bf1.md4);
    // printf(" me = %d\n", st.status.bf1.me);
    // printf(" mi = %d\n", st.status.bf1.mi);
    // printf("md5 = %d\n", st.status.bf1.md5);
    // printf(" fx = %d\n\n", st.status.bf1.fx3);
    // printf("[ 1 1 0 1 0 1 0 1 ]\n");
    // printf("cst = %d\n", st.status.bf1.cst);
    // printf("psr = %d\n", st.status.bf1.psr);
    // printf("ssr = %d\n", st.status.bf1.ssr);
    // printf("mds = %d\n", st.status.bf1.mds);
    // printf("ads = %d\n", st.status.bf1.ads);
    // printf("suc = %d\n", st.status.bf1.suc);
    // printf("aac = %d\n", st.status.bf1.aac);
    // printf(" fx = %d\n", st.status.bf1.fx4);
    // printf("[ 1 0 1 0 0 1 0 1 ]\n");
    // printf("sds  = %d\n", st.status.bf1.sds);
    // printf("ems  = %d\n", st.status.bf1.ems);
    // printf("pft  = %d\n", st.status.bf1.pft);
    // printf("fplt = %d\n", st.status.bf1.fplt);
    // printf("  fx = %d\n", st.status.bf1.fx5);
    return 0;
}
