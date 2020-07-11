
WEBSRC += \
	web/ui1.svg/innovaphone.ui1.svg.js

$(OUTDIR)/obj/ui1.svg_httpdata.cpp: $(IP_SRC)/web1/ui1.svg/ui1.svg.mak $(IP_SRC)/web1/ui1.svg/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.svg_httpdata.cpp \
		ui1.svg/innovaphone.ui1.svg.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/ui1.svg_httpdata.o
$(OUTDIR)/obj/ui1.svg_httpdata.o: $(OUTDIR)/obj/ui1.svg_httpdata.cpp
