
WEBSRC += \
	web/fonts/titilliumweb-regular.ttf

$(OUTDIR)/obj/fonts_httpdata.cpp: $(IP_SRC)/web1/fonts/*.*
		$(IP_SRC)/exe/httpfiles  $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/fonts_httpdata.cpp \
		fonts/titilliumweb-regular.ttf,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \

COMMONOBJS += $(OUTDIR)/obj/fonts_httpdata.o
$(OUTDIR)/obj/fonts_httpdata.o: $(OUTDIR)/obj/fonts_httpdata.cpp
