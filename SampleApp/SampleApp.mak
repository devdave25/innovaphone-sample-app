#----------------------------------------------------------------------------
# SampleApp.mak
# copyright (c) innovaphone 2015
#----------------------------------------------------------------------------

OUT = SampleApp

include sdk/sdk-defs.mak

include sdk/web1/appwebsocket/appwebsocket.mak
include sdk/web1/com.innovaphone.avatar/com.innovaphone.avatar.mak
include sdk/web1/fonts/fonts.mak
include sdk/web1/lib1/lib1.mak
include sdk/web1/ui1.lib/ui1.lib.mak

include SampleApp/SampleApp.mak

APP_OBJS += $(OUTDIR)/obj/SampleApp-main.o
$(OUTDIR)/obj/SampleApp-main.o: SampleApp-main.cpp force

include sdk/sdk.mak


