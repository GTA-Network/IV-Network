/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef IVData_h
#define IVData_h

#ifdef _CLIENT
#include <Common.h>
#endif

#define		ARRAY_ModelInfos				0x157D310 //0x15F73B0
#define		NUM_ModelInfos					31000
#define		ARRAY_WeaponInfos				0x1519370 //0x1540A20
#define		NUM_WeaponInfos					60

#define		MIN_INPUT_VALUE					0
#define		DEFAULT_BINARY_INPUT_VALUE		0
#define		DEFAULT_ANALOG_INPUT_VALUE		128
#define		MAX_INPUT_VALUE					255

#define		MAX_HISTORY_ITEMS				64

// Scrollbars
#define IV_MAX_SCROLLBARS 7
#define IV_MAX_SCROLLBAR_TEXT_LENGTH 1299
#define IV_SCROLLBAR_1_TEXT "BSHT+3%%  CUBEL+2%%  SPUK+1%%  CABOX-2%%  OOT+3%%  ECLA-7%%  BEAN-5%%  LOGR+3%%  RWDC-2%%  CHKO+6%%  BIGL-2%%       Sprunk overcomes aggressive Logger.       TIKL+59%%  FRUC-12%%  WHIZ+69%%  BADR+22%%  GNIC-32%%       Whiz has liquid assets worth over 1 Billion.       NXJN+36%%  XGAS+26%%  SYNC+8%%  RONO+16%%  GLBOIL+26%%       Economic growth eases slightly.       LSNW+3%%  METV-2%%  WZNT+2%%  CANE-3%%  LIBT+10%%  CNTU-2%%  EYEF+3%%       Corporate America braces for impact.       BOLS-10%%  JLZA+1%%  LOMB+17%%  FLEE-18%%  SHRK+20%%  BAWS-21%%       BNCO+3%%  BAWSAQ-2%%  PLAP+2%%  ERIS-3%%       Shares unruffled by surprise activist assault.       BETA+14%%  UGEN-1%%  MOLIS+8%%  MAXR-4%%  MTA+30%%       Energy bills cut for millions of people.       ~~~~~       "
#define IV_SCROLLBAR_2_TEXT "A new musical 'RAINCOAT EXPOSE' A real eye-opener at The Seagull Theater.       Tickets available for all shows at the eyefind.info box office.       Do not miss 'Banging trash can lids for an hour' at the Liberteen Theater  What a racket!       Magic Curtain Theater presents 'Swinging Puppets' and a fantastic new play 'Shakespeare on Drugs' The bard trip.       'The Flying Whore' at the Amdram Theatre  Enormous talents!  Needs to be seen to be believed!       'WTF' A tale of online love showing at The Maginot Theater.       You'll be LOL       ROFL       Returns after a sell out UK tour 'ABANDON SHIT' back at the Seagull Theater.       Performance Nonsense 'Fairy Body Paint' at the Liberteen Theater  What a big bunch of fairies.       ~~~~~       "
#define IV_SCROLLBAR_3_TEXT "IV:Net Credits"
#define IV_SCROLLBAR_4_TEXT "~~~~~       "
#define IV_SCROLLBAR_5_TEXT "autoeroticar.com       chiropracticovernight.com       ilovetoblow.org       a-thousand-words.net       libertytreeonline.com       babiesovernight.com       love-meet.net       loveyourmeat.com       nyan.cat       outsourceforamerica.com       pointclickshipabitch.com       weazelnews.com       piswasser.com       beanmachinecoffee.com       burgershot.net       electrictit.com       krapea.com       lipurgex.com       littlelacysurprisepageant.com       publiclibertyonline.com       vipluxuryringtones.com       americantravelguide.net       fruitcomputers.com       designerslave.com       erisfootware.com       eugenicsincorporated.com       flyhighpizzapie.com       gloryholethemepark.com       craplist.net       blogsnobs.org       libertycitypolice.com       sprunksoda.com       rustybrownsringdonuts.com       peepthatshit.com       lootandwank.com       myroomonline.net       dragonbrainthemovie.com       eatbiglogs.com       friendswithoutfaces.net       hornyhighschoolreunions.com       money2makemoney.com       poker-in-the-rear.com       redwoodcigarettes.com       roidsforlittleboys.com       "
#define IV_SCROLLBAR_6_TEXT "split sides proudly presents special guest -  ricky gervais - with resident comedian - katt williams -       "
#define IV_SCROLLBAR_7_TEXT "stay in sane       min speed 20 miles       max speed 30 miles       check your fuel       tiredness killed her       car thefts on the up. lock your car       be a courteous driver       watch your speed       "
#define IV_SCROLLBAR_8_TEXT "crime on an all time low.       ~~~~~       sudden influx illegal immigrants from balkan says mayor.       liberty city attracts more tourist than any other city in the world       "

// Area Names
#define IV_MAX_AREAS 128
#define IV_MAX_STREETS 128

#endif // IVData_h