
LIBBUILD = $(file < sdk/build.txt)
ifeq ($(LIBBUILD),)
LIBBUILD = $(BUILD)
endif

-include sdk/sdk-lib.mak

-include $(OUTDIR)/dep/*.dep

WEBSRCLIST_NOZIP = $(subst $(APPWEBPATH)/,,$(STARTHTMLS)) $(subst $(APPWEBPATH)/,,$(APPWEBSRC_NOZIP))
WEBSRCLIST_ZIP = $(subst $(APPWEBPATH)/,,$(APPWEBSRC_ZIP)) $(WEBSRC)

$(OUTDIR)/obj/innovaphone.manifest: $(STARTHTMLS) $(APPWEBSRC)
	echo ^<!-- innovaphone.manifest >$(OUTDIR)/obj/innovaphone.manifest
	echo { >>$(OUTDIR)/obj/innovaphone.manifest
	echo "files": >>$(OUTDIR)/obj/innovaphone.manifest
	echo [ >>$(OUTDIR)/obj/innovaphone.manifest
	echo "$(firstword $(WEBSRCLIST_NOZIP))">>$(OUTDIR)/obj/innovaphone.manifest
	$(foreach webfile,$(wordlist 2,$(words $(WEBSRCLIST_NOZIP)),$(WEBSRCLIST_NOZIP)),echo ,"$(webfile)">>$(OUTDIR)/obj/innovaphone.manifest &)
	$(foreach webfile,$(WEBSRCLIST_ZIP),echo ,"$(webfile)|gzip">>$(OUTDIR)/obj/innovaphone.manifest &)
	echo ] >>$(OUTDIR)/obj/innovaphone.manifest
	echo } >>$(OUTDIR)/obj/innovaphone.manifest
	echo --^> >>$(OUTDIR)/obj/innovaphone.manifest
	$(foreach htmlfile,$(STARTHTMLS),type $(subst /,\,$(OUTDIR)/obj/innovaphone.manifest) >$(OUTDIR)/obj/$(subst $(APPWEBPATH)/,,$(htmlfile)) &)
	$(foreach htmlfile,$(STARTHTMLS),type $(subst /,\,$(htmlfile)) >>$(OUTDIR)/obj/$(subst $(APPWEBPATH)/,,$(htmlfile)) &)

WINBINS := $(subst /,\,$(bins))
# we create the directories with a shell command before any target is executed, 
# as the directories have to exist before a target is executed and this creates issues with parallel builds
WINBINS_HACK := $(shell mkdir $(WINBINS) 2>NUL)

$(OUTDIR)/obj/%.o: $<
	$(CC) -MMD -MF $(OUTDIR)/dep/$(basename $(notdir $@)).dep $(INCLUDES) $(CFLAGS) $(APP_CFLAGS) -o $@ $<

$(OUTBIN)/$(OUT)/$(OUT): $(COMMONOBJS) $(APP_OBJS) $(LIB_SDK)
	$(CC) $(LFLAGS) -o $@ $(COMMONOBJS) $(APP_OBJS) $(LIBS) -L $(OUTSDK) -lsdk-$(LIBBUILD)

$(OUTBIN)/$(OUT)/$(OUT).debug: $(OUTBIN)/$(OUT)/$(OUT)
	$(OBJCPY) --only-keep-debug $(OUTBIN)/$(OUT)/$(OUT) $@
	$(OBJCPY) --strip-debug $(OUTBIN)/$(OUT)/$(OUT)
	$(OBJCPY) --add-gnu-debuglink $@ $(OUTBIN)/$(OUT)/$(OUT)
#	copy /b $(subst /,\\,$@)+,,

ifeq ($(DEBUG),1)
native x86_64 arm: $(OUTBIN)/$(OUT)/$(OUT)
else
native x86_64 arm: $(OUTBIN)/$(OUT)/$(OUT) $(OUTBIN)/$(OUT)/$(OUT).debug
endif

clean clean-x86_64 clean-arm: $(SDK_CLEANUP)
	$(foreach bin,$(WINBINS),@rd /S /Q $(bin) 2>NUL &)
	@echo "cleaned"

