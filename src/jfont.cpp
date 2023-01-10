#include "jfont.hpp"
/*----------------------------------------------------------------------------*/
/*	render_jstring() - to plot 16-dot Japanese bitmap font	*/
/*	Character code of the input string must be UTF-8		*/
int JpRender::render_jstring(int ix, int iy, char src[BUFSIZ]) {
  Charas charas;
  char str[BUFSIZ];
  char _dec_buf[BUFSIZ]; /* buf for decoded data (512 bytes) */
  char s[BUFSIZ], buf[BUFSIZ];
  char bmp[BUFSIZ];

  int len;
  int c1, c2, j1, j2;
  int n, nn, nmax;
  int w1, w2, h, b1, b2;
  int i, j, k, l;

  h = 16;  /* height */
  w1 = 8;  /* width1 (halfwidth) */
  w2 = 16; /* width2 (fullwidth) */
  b1 = (w1 + 7) / 8;
  b2 = (w2 + 7) / 8;
  nmax = _BMPNUM;

  if (strlen(src) > BUFSIZ - 2)
    src[BUFSIZ - 1] = 0; /* truncate the string for safety */

  utf82sjis(src, str); /* UTF-8 to SJIS conversion */
  len = strlen(str);

  for (i = 0; i < 4 * h; i++) bmp[i] = 0; /* clear bmp */

  n = 0;
  while ((c1 = (unsigned char)str[n]) != 0 && n < len) {
    if ((c1 > 0x80 && c1 < 0xa0) || c1 > 0xdf) { /* 1st byte of Kanji */
      n++;
      c2 = (unsigned char)str[n];                /* 2nd byte */
      _sjis2jis(c1, c2, &j1, &j2);               /* SJIS to JIS conversion */
      nn = 256 + (j1 - 0x21) * 94 + (j2 - 0x21); /* No. of the char */
      if (nn > 256 && nn < nmax)
        strcpy(s, charas._bmpb64[nn]); /* encoded bitmap */
      else
        strcpy(s, charas._bmpb64[256]);
      _b64decode(s, strlen(s), _dec_buf, &l);
      for (k = 0; k < l; k++) buf[k] = _dec_buf[k]; /* decoded bitmap */
      for (j = 0; j < h; j++) {
        for (i = 0; i < b2; i++) {
          bmp[(h - 1 - j) * 4 + i] =
              buf[j * b2 + i]; /* bmp: word-aligned, bottom up */
        }
      }
      glRasterPos2i(ix + w1 * (n - 1), iy);
      glBitmap(w2, h, 0, 0, w2, 0, (const GLubyte *)bmp);
    } else {   /* halfwidth */
      nn = c1; /* No. of the char */
      if (nn > 32 && nn < 256)
        strcpy(s, charas._bmpb64[nn]);
      else
        strcpy(s, charas._bmpb64[32]);
      _b64decode(s, strlen(s), _dec_buf, &l);
      for (k = 0; k < l; k++) {
        buf[k] = _dec_buf[k];
      }
      for (j = 0; j < h; j++) {
        for (i = 0; i < b1; i++) {
          bmp[(h - 1 - j) * 4 + i] = buf[j * b1 + i];
        }
      }
      glRasterPos2i(ix + w1 * n, iy);
      glBitmap(w1, h, 0, 0, w1, 0, (const GLubyte *)bmp);
    }
    n++;
  }

  return 0;
}

/* ---------------------------------------------------------------------------*/
/* SJIS to JIS  code conversion */
int JpRender::_sjis2jis(int s1, int s2, int *j1, int *j2)
/* input: s1(high),s2(low);  output: j1(high), j2(low) */
{
  s1 -= (s1 > 0x9f) ? 0xb1 : 0x71;
  s1 = s1 * 2 + 1;

  if (s2 > 0x9e) {
    s2 -= 0x7e;
    s1++;
  } else {
    if (s2 > 0x7e) s2--;
    s2 -= 0x1f;
  }

  *j1 = s1;
  *j2 = s2;

  return 0;
}

/* ---------------------------------------------------------------------------*/
/* Base64 decoder ( output to _dec_buf[] )	 */
int JpRender::_b64decode(char input[], int inputlen, char _dec_buf[],
                         int *outputlen) {
  Charas charas;
  char a0, a1, a2, a3;
  int i, k;
  int padnum;

  if ((inputlen % 4) != 0) {
    fprintf(stderr, "String length (%u) must be a multiple of 4.\n", inputlen);
    return 1;
  }

  padnum = 0;
  if (input[inputlen - 1] == '=') padnum++;
  if (input[inputlen - 2] == '=') padnum++;

  k = 0;
  for (i = 0; i < inputlen; i += 4) {
    k = (i / 4) * 3;

    a0 = (unsigned char)charas._dec_table[(int)input[i + 0]];
    a1 = (unsigned char)charas._dec_table[(int)input[i + 1]];
    a2 = (unsigned char)charas._dec_table[(int)input[i + 2]];
    a3 = (unsigned char)charas._dec_table[(int)input[i + 3]];

    _dec_buf[k + 0] = (char)((a0 << 2) + ((a1 & 0x30) >> 4));
    _dec_buf[k + 1] = (char)(((a1 & 0xF) << 4) + ((a2 & 0x3C) >> 2));
    _dec_buf[k + 2] = (char)(((a2 & 0x3) << 6) + (a3));

    /* clear the char right after the decoded data */
    if (i + 4 == inputlen) {
      _dec_buf[k + 3 - padnum] = 0;
      break;
    }
  }
  *outputlen = k + 3 - padnum; /* output length (bytes) */
  return 0;
}

/* ---------------------------------------------------------------------------*/
/* UTF-8 to SJIS conversion */
int JpRender::utf82sjis(char src[BUFSIZ], char dst[BUFSIZ]) {
  Charas charas;
  int len, ns, nd, c1, c2, c3;
  int uni, u1, u2;  // Unicode (UTF-16BE)
  int s1, s2;       // Shift_JIS
  int n;

  if (strlen(src) > BUFSIZ - 2)
    src[BUFSIZ - 1] = 0; /* truncate the string for safety */

  len = strlen(src);

  ns = 0;
  nd = 0;
  while ((c1 = (unsigned char)src[ns]) != 0 && ns < len) {
    ns++;
    if (c1 < 0x80) { /* 1-byte UTF-8 char */
      uni = c1;
    }

    else if (c1 >= 0xc2 && c1 <= 0xdf) { /* 2-byte UTF-8 char */
      c2 = (unsigned char)src[ns++];
      u1 = (c1 & 0x1c) >> 2;
      u2 = (c1 & 0x03) << 6 | (c2 & 0x3f);
      uni = u1 * 256 + u2;
    }

    else if (c1 >= 0xe0 && c1 <= 0xef) { /* 3-byte UTF-8 char */
      c2 = (unsigned char)src[ns++];
      c3 = (unsigned char)src[ns++];
      u1 = (c1 & 0x0f) << 4 | (c2 & 0x3c) >> 2;
      u2 = (c2 & 0x03) << 6 | (c3 & 0x3f);
      uni = u1 * 256 + u2;
    }

    else {                              /* 4 to 6-byte UTF-8 */
      if ((c1 & 0xf8) == 0xf0) ns += 3; /* 4-byte */
      if ((c1 & 0xfc) == 0xf8) ns += 4; /* 5-byte */
      if ((c1 & 0xfe) == 0xfc) ns += 5; /* 6-byte */
      uni = -1;
      dst[nd++] = 0x20;
    }

    if (uni > 0) {
      n = (uni < 0xa000) ? uni : uni - 0x5900;
      s1 = charas._unitbl[n] / 256;
      s2 = charas._unitbl[n] % 256;
      if (s1 == 0) {
        if (s2 == 0)
          dst[nd++] = 0x20; /* undefined */
        else
          dst[nd++] = s2;
      } else {
        dst[nd++] = s1;
        dst[nd++] = s2;
      }
    }
  }
  dst[nd] = 0;

  return 0;
}