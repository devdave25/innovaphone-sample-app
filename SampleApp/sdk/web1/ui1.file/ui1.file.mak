
WEBSRC += \
	web/ui1.file/innovaphone.ui1.file.js

$(OUTDIR)/obj/ui1.file_httpdata.cpp: $(IP_SRC)/web1/ui1.file/ui1.file.mak $(IP_SRC)/web1/ui1.file/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/ui1.file_httpdata.cpp \
		ui1.file/innovaphone.ui1.file.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD \

COMMONOBJS += $(OUTDIR)/obj/ui1.file_httpdata.o
$(OUTDIR)/obj/ui1.file_httpdata.o: $(OUTDIR)/obj/ui1.file_httpdata.cpp
