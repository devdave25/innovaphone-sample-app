
WEBSRC += \
	web1/lib1/innovaphone.lib1.js \
	web1/lib1/innovaphone.lib1.css

$(OUTDIR)/obj/lib1_httpdata.cpp: $(IP_SRC)/web1/lib1/lib1.mak $(IP_SRC)/web1/lib1/*.js $(IP_SRC)/web1/lib1/*.css
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/lib1_httpdata.cpp \
		lib1/innovaphone.lib1.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \
		lib1/innovaphone.lib1.css,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \

COMMONOBJS += $(OUTDIR)/obj/lib1_httpdata.o
$(OUTDIR)/obj/lib1_httpdata.o: $(OUTDIR)/obj/lib1_httpdata.cpp
