/* Copyright (C) 2004 Jean-Marc Valin */
/**
   @file filters_arm4.h
   @brief Various analysis/synthesis filters (ARM4 version)
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

#define OVERRIDE_NORMALIZE16
int normalize16(const spx_sig_t *x, spx_word16_t *y, spx_sig_t max_scale, int len)
{
   spx_sig_t max_val = 1.0f;
   int sig_shift = 0;
   
   // Find the maximum absolute value in the array
   for (int i = 0; i < len; i++) {
      spx_sig_t abs_val = x[i] < 0 ? -x[i] : x[i];
      if (abs_val > max_val) {
         max_val = abs_val;
      }
   }
   
   // Compute the required shift
   while (max_val > max_scale) {
      sig_shift++;
      max_val *= 0.5f; // Equivalent to right shift for floats
   }
   
   // Normalize the values and scale down
   for (int i = 0; i < len; i++) {
      spx_sig_t scaled_val = x[i] * (1 << sig_shift); // Scale up
      y[i] = (spx_word16_t)(scaled_val);
   }
   
   return sig_shift;
}
