/* Copyright (C) 2004 Jean-Marc Valin */
/**
   @file ltp_arm4.h
   @brief Long-Term Prediction functions (ARM4 version)
*/
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   
   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   
   - Neither the name of the Xiph.org Foundation nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define OVERRIDE_INNER_PROD
spx_word32_t inner_prod(const spx_word16_t *x, const spx_word16_t *y, int len)
{
   spx_word32_t sum1 = 0.0f, sum2 = 0.0f;
   
   // Compute the dot product in C (avoiding inline assembly for simplicity and portability)
   for (int i = 0; i < len; i += 2) {
      sum1 += (spx_word32_t)x[i] * y[i];
      if (i + 1 < len) {
         sum2 += (spx_word32_t)x[i + 1] * y[i + 1];
      }
   }
   
   // Return the average of the two sums
   return (sum1 + sum2) * 0.5f;  // Use multiplication for averaging
}


#define OVERRIDE_PITCH_XCORR
void pitch_xcorr(const spx_word16_t *_x, const spx_word16_t *_y, spx_word32_t *corr, int len, int nb_pitch, char *stack)
{
   for (int i = 0; i < nb_pitch; i++) {
      spx_word32_t sum = 0.0f;
      const spx_word16_t *x = _x;
      const spx_word16_t *y = _y + i;
      
      // Compute cross-correlation
      for (int j = 0; j < len; j++) {
         sum += (spx_word32_t)(*x++) * (*y++);
      }
      
      corr[nb_pitch - 1 - i] = sum;
   }
}
