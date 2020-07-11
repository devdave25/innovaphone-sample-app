
WEBSRC += \
	web/crypto/innovaphone.crypto.js

$(OUTDIR)/obj/crypto_httpdata.cpp: $(IP_SRC)/web1/crypto/crypto.mak $(IP_SRC)/web1/crypto/*.js
		$(IP_SRC)/exe/httpfiles $(HTTPFILES-WEB-FLAGS) -d $(IP_SRC)/web1 -o $(OUTDIR)/obj/crypto_httpdata.cpp \
		crypto/innovaphone.crypto.js,SERVLET_STATIC,HTTP_CACHE+HTTP_NOPWD+HTTP_FORCENOPWD

COMMONOBJS += $(OUTDIR)/obj/crypto_httpdata.o
$(OUTDIR)/obj/crypto_httpdata.o: $(OUTDIR)/obj/crypto_httpdata.cpp
