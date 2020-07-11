
WEBSRC += \
	web/config/innovaphone.config.js

$(OUTDIR)/obj/config_httpdata.cpp: $(IP_SRC)/web1/config/config.mak $(IP_SRC)/web1/config/*.js 
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/config_httpdata.cpp \
		config/innovaphone.config.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD 

COMMONOBJS += $(OUTDIR)/obj/config_httpdata.o
$(OUTDIR)/obj/config_httpdata.o: $(OUTDIR)/obj/config_httpdata.cpp
