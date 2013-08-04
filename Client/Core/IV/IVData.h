//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: IVData.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef IVData_h
#define IVData_h

#include <Common.h>

// Scrollbars
#define IV_MAX_SCROLLBARS 7
#define IV_MAX_SCROLLBAR_TEXT_LENGTH 1299
#define IV_SCROLLBAR_1_TEXT "BSHT+3%%  CUBEL+2%%  SPUK+1%%  CABOX-2%%  OOT+3%%  ECLA-7%%  BEAN-5%%  LOGR+3%%  RWDC-2%%  CHKO+6%%  BIGL-2%%       Sprunk overcomes aggressive Logger.       TIKL+59%%  FRUC-12%%  WHIZ+69%%  BADR+22%%  GNIC-32%%       Whiz has liquid assets worth over 1 Billion.       NXJN+36%%  XGAS+26%%  SYNC+8%%  RONO+16%%  GLBOIL+26%%       Economic growth eases slightly.       LSNW+3%%  METV-2%%  WZNT+2%%  CANE-3%%  LIBT+10%%  CNTU-2%%  EYEF+3%%       Corporate America braces for impact.       BOLS-10%%  JLZA+1%%  LOMB+17%%  FLEE-18%%  SHRK+20%%  BAWS-21%%       Only one in five SA:MP players have left their house this year.       BNCO+3%%  BAWSAQ-2%%  PLAP+2%%  ERIS-3%%       Shares unruffled by surprise activist assault.       BETA+14%%  UGEN-1%%  MOLIS+8%%  MAXR-4%%  MTA+30%%       Energy bills cut for millions of people.       ~~~~~       "
#define IV_SCROLLBAR_2_TEXT "A new musical 'RAINCOAT EXPOSE' A real eye-opener at The Seagull Theater.       Tickets available for all shows at the eyefind.info box office.       Do not miss 'Banging trash can lids for an hour' at the Liberteen Theater  What a racket!       Magic Curtain Theater presents 'Swinging Puppets' and a fantastic new play 'Shakespeare on Drugs' The bard trip.       'The Flying Whore' at the Amdram Theatre  Enormous talents!  Needs to be seen to be believed!       'WTF' A tale of online love showing at The Maginot Theater.       You'll be LOL       ROFL       Returns after a sell out UK tour 'ABANDON SHIT' back at the Seagull Theater.       Performance Nonsense 'Fairy Body Paint' at the Liberteen Theater  What a big bunch of fairies.       ~~~~~       "
#define IV_SCROLLBAR_3_TEXT "IV:MP Credits"
#define IV_SCROLLBAR_4_TEXT "~~~~~       "
#define IV_SCROLLBAR_5_TEXT "autoeroticar.com       chiropracticovernight.com       ilovetoblow.org       a-thousand-words.net       libertytreeonline.com       babiesovernight.com       love-meet.net       loveyourmeat.com       nyan.cat       outsourceforamerica.com       pointclickshipabitch.com       weazelnews.com       piswasser.com       beanmachinecoffee.com       burgershot.net       electrictit.com       krapea.com       lipurgex.com       littlelacysurprisepageant.com       publiclibertyonline.com       vipluxuryringtones.com       americantravelguide.net       fruitcomputers.com       designerslave.com       erisfootware.com       eugenicsincorporated.com       flyhighpizzapie.com       gloryholethemepark.com       craplist.net       blogsnobs.org       libertycitypolice.com       sprunksoda.com       rustybrownsringdonuts.com       peepthatshit.com       lootandwank.com       myroomonline.net       dragonbrainthemovie.com       eatbiglogs.com       friendswithoutfaces.net       hornyhighschoolreunions.com       money2makemoney.com       poker-in-the-rear.com       redwoodcigarettes.com       roidsforlittleboys.com       "
#define IV_SCROLLBAR_6_TEXT "split sides proudly presents special guest -  ricky gervais - with resident comedian - katt williams -       "
#define IV_SCROLLBAR_7_TEXT "stay in sane       min speed 20 miles       max speed 30 miles       check your fuel       tiredness killed her       car thefts on the up. lock your car       be a courteous driver       watch your speed       "
#define IV_SCROLLBAR_8_TEXT "crime on an all time low.       ~~~~~       sudden influx illegal immigrants from balkan says mayor.       liberty city attracts more tourist than any other city in the world       "

struct sScrollBarInfo
{
	unsigned iID;
	CString strLocation;
	CString strDefaultText;
};

sScrollBarInfo scrollBarItems[] =
{
	{0, "Financial", IV_SCROLLBAR_1_TEXT},
	{1, "Theatre", IV_SCROLLBAR_2_TEXT},
	{2, "Advertising", IV_SCROLLBAR_3_TEXT},
	{3, "Clock", IV_SCROLLBAR_4_TEXT},
	{4, "URIs", IV_SCROLLBAR_5_TEXT},
	{5, "ComedyClub", IV_SCROLLBAR_6_TEXT},
	{6, "Traffic(Tunnel)", IV_SCROLLBAR_7_TEXT},
	{7, "News", IV_SCROLLBAR_8_TEXT},
};

// Area Names
#define IV_MAX_AREAS 128
#define IV_MAX_STREETS 128

#endif // IVData_h