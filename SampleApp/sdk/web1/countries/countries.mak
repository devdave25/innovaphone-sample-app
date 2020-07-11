
WEBSRC += \
	web/countries/innovaphone.countries.js

$(OUTDIR)/obj/countries_httpdata.cpp: $(IP_SRC)/web1/countries/countries.mak $(IP_SRC)/web1/countries/*.js 
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/countries_httpdata.cpp \
		countries/innovaphone.countries.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD 

COMMONOBJS += $(OUTDIR)/obj/countries_httpdata.o
$(OUTDIR)/obj/countries_httpdata.o: $(OUTDIR)/obj/countries_httpdata.cpp
