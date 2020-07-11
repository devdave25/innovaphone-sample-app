
WEBSRC += \
	web/phpsession/innovaphone.phpsession.js

$(OUTDIR)/obj/phpsession_httpdata.cpp: $(IP_SRC)/web1/phpsession/phpsession.mak $(IP_SRC)/web1/phpsession/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/phpsession_httpdata.cpp \
		phpsession/innovaphone.phpsession.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/phpsession_httpdata.o
$(OUTDIR)/obj/phpsession_httpdata.o: $(OUTDIR)/obj/phpsession_httpdata.cpp
