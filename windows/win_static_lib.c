/*************************************************************************/
/*                                                                       */
/*                  Language Technologies Institute                      */
/*                     Carnegie Mellon University                        */
/*                        Copyright (c) 2000                             */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  CARNEGIE MELLON UNIVERSITY AND THE CONTRIBUTORS TO THIS WORK         */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL CARNEGIE MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE      */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  Additional defines needed to use this as a VS 2017 static library    */
/*  These are written by config on Makefile platforms                    */
/*                                                                       */
/*************************************************************************/

#include "flite.h"

/* Deliberately skipping cmu_time_awb */
cst_voice *register_cmu_us_kal(const char *voxdir);
cst_voice *register_cmu_us_kal16(const char *voxdir);
cst_voice *register_cmu_us_awb(const char *voxdir);
cst_voice *register_cmu_us_rms(const char *voxdir);
cst_voice *register_cmu_us_slt(const char *voxdir);

void usenglish_init(cst_voice *v);
void cmu_indic_lang_init(cst_voice *v);
void cmu_grapheme_lang_init(cst_voice *v);
cst_lexicon *cmu_lex_init(void);
cst_lexicon *cmu_indic_lex_init(void);
cst_lexicon *cmu_grapheme_lex_init(void);

cst_val *flite_set_voice_list(const char *voxdir)
{
	/* First in list is default voice */
	flite_voice_list = cons_val(voice_val(register_cmu_us_kal(voxdir)), flite_voice_list);
	flite_voice_list = cons_val(voice_val(register_cmu_us_kal16(voxdir)), flite_voice_list);
	flite_voice_list = cons_val(voice_val(register_cmu_us_awb(voxdir)), flite_voice_list);
	flite_voice_list = cons_val(voice_val(register_cmu_us_rms(voxdir)), flite_voice_list);
	flite_voice_list = cons_val(voice_val(register_cmu_us_slt(voxdir)), flite_voice_list);
	flite_voice_list = val_reverse(flite_voice_list);
	return flite_voice_list;
}

void flite_set_lang_list(void)
{
	flite_add_lang("eng", usenglish_init, cmu_lex_init);
	flite_add_lang("cmu_indic_lang", cmu_indic_lang_init, cmu_indic_lex_init);
	flite_add_lang("cmu_grapheme_lang", cmu_grapheme_lang_init, cmu_grapheme_lex_init);
}