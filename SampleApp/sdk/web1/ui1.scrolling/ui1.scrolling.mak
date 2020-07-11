
WEBSRC += \
	web/ui1.scrolling/innovaphone.ui1.scrolling.js

$(OUTDIR)/obj/ui1.scrolling_httpdata.cpp: $(IP_SRC)/web1/ui1.scrolling/ui1.scrolling.mak $(IP_SRC)/web1/ui1.scrolling/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.scrolling_httpdata.cpp \
		ui1.scrolling/innovaphone.ui1.scrolling.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/ui1.scrolling_httpdata.o
$(OUTDIR)/obj/ui1.scrolling_httpdata.o: $(OUTDIR)/obj/ui1.scrolling_httpdata.cpp
