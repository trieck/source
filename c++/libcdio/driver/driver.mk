##
## Auto Generated makefile, please do not edit
##
ProjectName:=driver

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "D:\source\c++\libcdio"
ProjectPath            := "D:\source\c++\libcdio\driver"
CurrentFileName        :=
CurrentFulePath        :=
CurrentFileFullPath    :=
User                   :=trieck
Date                   :=11/23/09
CodeLitePath           :="d:\Program Files\CodeLite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=$(PreprocessorSwitch)HAVE_CONFIG_H $(PreprocessorSwitch)EXTERNAL_LIBCDIO_CONFIG_H 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            := "$(IncludeSwitch)D:/MinGW/include"  "$(IncludeSwitch)." "$(IncludeSwitch)../" "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" "$(IncludeSwitch).." "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" 
RcIncludePath          :=
Libs                   :=
LibPath                :="$(LibraryPathSwitch)D:/MinGW/Lib"  "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix) $(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix) $(IntermediateDirectory)/_cdio_stream$(ObjectSuffix) $(IntermediateDirectory)/aix$(ObjectSuffix) $(IntermediateDirectory)/audio$(ObjectSuffix) $(IntermediateDirectory)/bsdi$(ObjectSuffix) $(IntermediateDirectory)/cd_types$(ObjectSuffix) $(IntermediateDirectory)/cdio$(ObjectSuffix) $(IntermediateDirectory)/cdtext$(ObjectSuffix) $(IntermediateDirectory)/device$(ObjectSuffix) \
	$(IntermediateDirectory)/disc$(ObjectSuffix) $(IntermediateDirectory)/ds$(ObjectSuffix) $(IntermediateDirectory)/gnu_linux$(ObjectSuffix) $(IntermediateDirectory)/image_common$(ObjectSuffix) $(IntermediateDirectory)/logging$(ObjectSuffix) $(IntermediateDirectory)/mmc$(ObjectSuffix) $(IntermediateDirectory)/netbsd$(ObjectSuffix) $(IntermediateDirectory)/os2$(ObjectSuffix) $(IntermediateDirectory)/osx$(ObjectSuffix) $(IntermediateDirectory)/read$(ObjectSuffix) \
	$(IntermediateDirectory)/sector$(ObjectSuffix) $(IntermediateDirectory)/solaris$(ObjectSuffix) $(IntermediateDirectory)/track$(ObjectSuffix) $(IntermediateDirectory)/utf8$(ObjectSuffix) $(IntermediateDirectory)/util$(ObjectSuffix) $(IntermediateDirectory)/aspi32$(ObjectSuffix) $(IntermediateDirectory)/win32$(ObjectSuffix) $(IntermediateDirectory)/win32_ioctl$(ObjectSuffix) $(IntermediateDirectory)/freebsd$(ObjectSuffix) $(IntermediateDirectory)/freebsd_cam$(ObjectSuffix) \
	$(IntermediateDirectory)/freebsd_ioctl$(ObjectSuffix) $(IntermediateDirectory)/bincue$(ObjectSuffix) $(IntermediateDirectory)/cdrdao$(ObjectSuffix) $(IntermediateDirectory)/nrg$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@makedir $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

./Debug:
	@makedir "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix): ../../../../libcdio/lib/driver/_cdio_generic.c $(IntermediateDirectory)/_cdio_generic$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/_cdio_generic.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/_cdio_generic$(DependSuffix): ../../../../libcdio/lib/driver/_cdio_generic.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix) -MF$(IntermediateDirectory)/_cdio_generic$(DependSuffix) -MM "D:/libcdio/lib/driver/_cdio_generic.c"

$(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix): ../../../../libcdio/lib/driver/_cdio_stdio.c $(IntermediateDirectory)/_cdio_stdio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/_cdio_stdio.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/_cdio_stdio$(DependSuffix): ../../../../libcdio/lib/driver/_cdio_stdio.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix) -MF$(IntermediateDirectory)/_cdio_stdio$(DependSuffix) -MM "D:/libcdio/lib/driver/_cdio_stdio.c"

$(IntermediateDirectory)/_cdio_stream$(ObjectSuffix): ../../../../libcdio/lib/driver/_cdio_stream.c $(IntermediateDirectory)/_cdio_stream$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/_cdio_stream.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/_cdio_stream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/_cdio_stream$(DependSuffix): ../../../../libcdio/lib/driver/_cdio_stream.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/_cdio_stream$(ObjectSuffix) -MF$(IntermediateDirectory)/_cdio_stream$(DependSuffix) -MM "D:/libcdio/lib/driver/_cdio_stream.c"

$(IntermediateDirectory)/aix$(ObjectSuffix): ../../../../libcdio/lib/driver/aix.c $(IntermediateDirectory)/aix$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/aix.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aix$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aix$(DependSuffix): ../../../../libcdio/lib/driver/aix.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aix$(ObjectSuffix) -MF$(IntermediateDirectory)/aix$(DependSuffix) -MM "D:/libcdio/lib/driver/aix.c"

$(IntermediateDirectory)/audio$(ObjectSuffix): ../../../../libcdio/lib/driver/audio.c $(IntermediateDirectory)/audio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/audio.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/audio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/audio$(DependSuffix): ../../../../libcdio/lib/driver/audio.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/audio$(ObjectSuffix) -MF$(IntermediateDirectory)/audio$(DependSuffix) -MM "D:/libcdio/lib/driver/audio.c"

$(IntermediateDirectory)/bsdi$(ObjectSuffix): ../../../../libcdio/lib/driver/bsdi.c $(IntermediateDirectory)/bsdi$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/bsdi.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/bsdi$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bsdi$(DependSuffix): ../../../../libcdio/lib/driver/bsdi.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/bsdi$(ObjectSuffix) -MF$(IntermediateDirectory)/bsdi$(DependSuffix) -MM "D:/libcdio/lib/driver/bsdi.c"

$(IntermediateDirectory)/cd_types$(ObjectSuffix): ../../../../libcdio/lib/driver/cd_types.c $(IntermediateDirectory)/cd_types$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/cd_types.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cd_types$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cd_types$(DependSuffix): ../../../../libcdio/lib/driver/cd_types.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cd_types$(ObjectSuffix) -MF$(IntermediateDirectory)/cd_types$(DependSuffix) -MM "D:/libcdio/lib/driver/cd_types.c"

$(IntermediateDirectory)/cdio$(ObjectSuffix): ../../../../libcdio/lib/driver/cdio.c $(IntermediateDirectory)/cdio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/cdio.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cdio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cdio$(DependSuffix): ../../../../libcdio/lib/driver/cdio.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cdio$(ObjectSuffix) -MF$(IntermediateDirectory)/cdio$(DependSuffix) -MM "D:/libcdio/lib/driver/cdio.c"

$(IntermediateDirectory)/cdtext$(ObjectSuffix): ../../../../libcdio/lib/driver/cdtext.c $(IntermediateDirectory)/cdtext$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/cdtext.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cdtext$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cdtext$(DependSuffix): ../../../../libcdio/lib/driver/cdtext.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cdtext$(ObjectSuffix) -MF$(IntermediateDirectory)/cdtext$(DependSuffix) -MM "D:/libcdio/lib/driver/cdtext.c"

$(IntermediateDirectory)/device$(ObjectSuffix): ../../../../libcdio/lib/driver/device.c $(IntermediateDirectory)/device$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/device.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/device$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/device$(DependSuffix): ../../../../libcdio/lib/driver/device.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/device$(ObjectSuffix) -MF$(IntermediateDirectory)/device$(DependSuffix) -MM "D:/libcdio/lib/driver/device.c"

$(IntermediateDirectory)/disc$(ObjectSuffix): ../../../../libcdio/lib/driver/disc.c $(IntermediateDirectory)/disc$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/disc.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/disc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/disc$(DependSuffix): ../../../../libcdio/lib/driver/disc.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/disc$(ObjectSuffix) -MF$(IntermediateDirectory)/disc$(DependSuffix) -MM "D:/libcdio/lib/driver/disc.c"

$(IntermediateDirectory)/ds$(ObjectSuffix): ../../../../libcdio/lib/driver/ds.c $(IntermediateDirectory)/ds$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/ds.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ds$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ds$(DependSuffix): ../../../../libcdio/lib/driver/ds.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ds$(ObjectSuffix) -MF$(IntermediateDirectory)/ds$(DependSuffix) -MM "D:/libcdio/lib/driver/ds.c"

$(IntermediateDirectory)/gnu_linux$(ObjectSuffix): ../../../../libcdio/lib/driver/gnu_linux.c $(IntermediateDirectory)/gnu_linux$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/gnu_linux.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gnu_linux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gnu_linux$(DependSuffix): ../../../../libcdio/lib/driver/gnu_linux.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/gnu_linux$(ObjectSuffix) -MF$(IntermediateDirectory)/gnu_linux$(DependSuffix) -MM "D:/libcdio/lib/driver/gnu_linux.c"

$(IntermediateDirectory)/image_common$(ObjectSuffix): ../../../../libcdio/lib/driver/image_common.c $(IntermediateDirectory)/image_common$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/image_common.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/image_common$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/image_common$(DependSuffix): ../../../../libcdio/lib/driver/image_common.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/image_common$(ObjectSuffix) -MF$(IntermediateDirectory)/image_common$(DependSuffix) -MM "D:/libcdio/lib/driver/image_common.c"

$(IntermediateDirectory)/logging$(ObjectSuffix): ../../../../libcdio/lib/driver/logging.c $(IntermediateDirectory)/logging$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/logging.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/logging$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/logging$(DependSuffix): ../../../../libcdio/lib/driver/logging.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/logging$(ObjectSuffix) -MF$(IntermediateDirectory)/logging$(DependSuffix) -MM "D:/libcdio/lib/driver/logging.c"

$(IntermediateDirectory)/mmc$(ObjectSuffix): ../../../../libcdio/lib/driver/mmc.c $(IntermediateDirectory)/mmc$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/mmc.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/mmc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mmc$(DependSuffix): ../../../../libcdio/lib/driver/mmc.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/mmc$(ObjectSuffix) -MF$(IntermediateDirectory)/mmc$(DependSuffix) -MM "D:/libcdio/lib/driver/mmc.c"

$(IntermediateDirectory)/netbsd$(ObjectSuffix): ../../../../libcdio/lib/driver/netbsd.c $(IntermediateDirectory)/netbsd$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/netbsd.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/netbsd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/netbsd$(DependSuffix): ../../../../libcdio/lib/driver/netbsd.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/netbsd$(ObjectSuffix) -MF$(IntermediateDirectory)/netbsd$(DependSuffix) -MM "D:/libcdio/lib/driver/netbsd.c"

$(IntermediateDirectory)/os2$(ObjectSuffix): ../../../../libcdio/lib/driver/os2.c $(IntermediateDirectory)/os2$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/os2.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/os2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/os2$(DependSuffix): ../../../../libcdio/lib/driver/os2.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/os2$(ObjectSuffix) -MF$(IntermediateDirectory)/os2$(DependSuffix) -MM "D:/libcdio/lib/driver/os2.c"

$(IntermediateDirectory)/osx$(ObjectSuffix): ../../../../libcdio/lib/driver/osx.c $(IntermediateDirectory)/osx$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/osx.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/osx$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osx$(DependSuffix): ../../../../libcdio/lib/driver/osx.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/osx$(ObjectSuffix) -MF$(IntermediateDirectory)/osx$(DependSuffix) -MM "D:/libcdio/lib/driver/osx.c"

$(IntermediateDirectory)/read$(ObjectSuffix): ../../../../libcdio/lib/driver/read.c $(IntermediateDirectory)/read$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/read.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/read$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/read$(DependSuffix): ../../../../libcdio/lib/driver/read.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/read$(ObjectSuffix) -MF$(IntermediateDirectory)/read$(DependSuffix) -MM "D:/libcdio/lib/driver/read.c"

$(IntermediateDirectory)/sector$(ObjectSuffix): ../../../../libcdio/lib/driver/sector.c $(IntermediateDirectory)/sector$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/sector.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sector$(DependSuffix): ../../../../libcdio/lib/driver/sector.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sector$(ObjectSuffix) -MF$(IntermediateDirectory)/sector$(DependSuffix) -MM "D:/libcdio/lib/driver/sector.c"

$(IntermediateDirectory)/solaris$(ObjectSuffix): ../../../../libcdio/lib/driver/solaris.c $(IntermediateDirectory)/solaris$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/solaris.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/solaris$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/solaris$(DependSuffix): ../../../../libcdio/lib/driver/solaris.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/solaris$(ObjectSuffix) -MF$(IntermediateDirectory)/solaris$(DependSuffix) -MM "D:/libcdio/lib/driver/solaris.c"

$(IntermediateDirectory)/track$(ObjectSuffix): ../../../../libcdio/lib/driver/track.c $(IntermediateDirectory)/track$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/track.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/track$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/track$(DependSuffix): ../../../../libcdio/lib/driver/track.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/track$(ObjectSuffix) -MF$(IntermediateDirectory)/track$(DependSuffix) -MM "D:/libcdio/lib/driver/track.c"

$(IntermediateDirectory)/utf8$(ObjectSuffix): ../../../../libcdio/lib/driver/utf8.c $(IntermediateDirectory)/utf8$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/utf8.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/utf8$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utf8$(DependSuffix): ../../../../libcdio/lib/driver/utf8.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/utf8$(ObjectSuffix) -MF$(IntermediateDirectory)/utf8$(DependSuffix) -MM "D:/libcdio/lib/driver/utf8.c"

$(IntermediateDirectory)/util$(ObjectSuffix): ../../../../libcdio/lib/driver/util.c $(IntermediateDirectory)/util$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/util.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/util$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util$(DependSuffix): ../../../../libcdio/lib/driver/util.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/util$(ObjectSuffix) -MF$(IntermediateDirectory)/util$(DependSuffix) -MM "D:/libcdio/lib/driver/util.c"

$(IntermediateDirectory)/aspi32$(ObjectSuffix): ../../../../libcdio/lib/driver/MSWindows/aspi32.c $(IntermediateDirectory)/aspi32$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/MSWindows/aspi32.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aspi32$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aspi32$(DependSuffix): ../../../../libcdio/lib/driver/MSWindows/aspi32.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aspi32$(ObjectSuffix) -MF$(IntermediateDirectory)/aspi32$(DependSuffix) -MM "D:/libcdio/lib/driver/MSWindows/aspi32.c"

$(IntermediateDirectory)/win32$(ObjectSuffix): ../../../../libcdio/lib/driver/MSWindows/win32.c $(IntermediateDirectory)/win32$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/MSWindows/win32.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/win32$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/win32$(DependSuffix): ../../../../libcdio/lib/driver/MSWindows/win32.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/win32$(ObjectSuffix) -MF$(IntermediateDirectory)/win32$(DependSuffix) -MM "D:/libcdio/lib/driver/MSWindows/win32.c"

$(IntermediateDirectory)/win32_ioctl$(ObjectSuffix): ../../../../libcdio/lib/driver/MSWindows/win32_ioctl.c $(IntermediateDirectory)/win32_ioctl$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/MSWindows/win32_ioctl.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/win32_ioctl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/win32_ioctl$(DependSuffix): ../../../../libcdio/lib/driver/MSWindows/win32_ioctl.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/win32_ioctl$(ObjectSuffix) -MF$(IntermediateDirectory)/win32_ioctl$(DependSuffix) -MM "D:/libcdio/lib/driver/MSWindows/win32_ioctl.c"

$(IntermediateDirectory)/freebsd$(ObjectSuffix): ../../../../libcdio/lib/driver/FreeBSD/freebsd.c $(IntermediateDirectory)/freebsd$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/FreeBSD/freebsd.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freebsd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freebsd$(DependSuffix): ../../../../libcdio/lib/driver/FreeBSD/freebsd.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freebsd$(ObjectSuffix) -MF$(IntermediateDirectory)/freebsd$(DependSuffix) -MM "D:/libcdio/lib/driver/FreeBSD/freebsd.c"

$(IntermediateDirectory)/freebsd_cam$(ObjectSuffix): ../../../../libcdio/lib/driver/FreeBSD/freebsd_cam.c $(IntermediateDirectory)/freebsd_cam$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/FreeBSD/freebsd_cam.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freebsd_cam$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freebsd_cam$(DependSuffix): ../../../../libcdio/lib/driver/FreeBSD/freebsd_cam.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freebsd_cam$(ObjectSuffix) -MF$(IntermediateDirectory)/freebsd_cam$(DependSuffix) -MM "D:/libcdio/lib/driver/FreeBSD/freebsd_cam.c"

$(IntermediateDirectory)/freebsd_ioctl$(ObjectSuffix): ../../../../libcdio/lib/driver/FreeBSD/freebsd_ioctl.c $(IntermediateDirectory)/freebsd_ioctl$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/FreeBSD/freebsd_ioctl.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/freebsd_ioctl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/freebsd_ioctl$(DependSuffix): ../../../../libcdio/lib/driver/FreeBSD/freebsd_ioctl.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/freebsd_ioctl$(ObjectSuffix) -MF$(IntermediateDirectory)/freebsd_ioctl$(DependSuffix) -MM "D:/libcdio/lib/driver/FreeBSD/freebsd_ioctl.c"

$(IntermediateDirectory)/bincue$(ObjectSuffix): ../../../../libcdio/lib/driver/image/bincue.c $(IntermediateDirectory)/bincue$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/image/bincue.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/bincue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bincue$(DependSuffix): ../../../../libcdio/lib/driver/image/bincue.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/bincue$(ObjectSuffix) -MF$(IntermediateDirectory)/bincue$(DependSuffix) -MM "D:/libcdio/lib/driver/image/bincue.c"

$(IntermediateDirectory)/cdrdao$(ObjectSuffix): ../../../../libcdio/lib/driver/image/cdrdao.c $(IntermediateDirectory)/cdrdao$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/image/cdrdao.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cdrdao$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cdrdao$(DependSuffix): ../../../../libcdio/lib/driver/image/cdrdao.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cdrdao$(ObjectSuffix) -MF$(IntermediateDirectory)/cdrdao$(DependSuffix) -MM "D:/libcdio/lib/driver/image/cdrdao.c"

$(IntermediateDirectory)/nrg$(ObjectSuffix): ../../../../libcdio/lib/driver/image/nrg.c $(IntermediateDirectory)/nrg$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/image/nrg.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/nrg$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nrg$(DependSuffix): ../../../../libcdio/lib/driver/image/nrg.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/nrg$(ObjectSuffix) -MF$(IntermediateDirectory)/nrg$(DependSuffix) -MM "D:/libcdio/lib/driver/image/nrg.c"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/_cdio_generic$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_generic$(DependSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_generic$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stdio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stdio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aix$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aix$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aix$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/audio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/audio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/audio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bsdi$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bsdi$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bsdi$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cd_types$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cd_types$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cd_types$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cdtext$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cdtext$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cdtext$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/device$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/device$(DependSuffix)
	$(RM) $(IntermediateDirectory)/device$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/disc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/disc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/disc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ds$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ds$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ds$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gnu_linux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gnu_linux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gnu_linux$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/image_common$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/image_common$(DependSuffix)
	$(RM) $(IntermediateDirectory)/image_common$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/logging$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/logging$(DependSuffix)
	$(RM) $(IntermediateDirectory)/logging$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mmc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mmc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mmc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/netbsd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/netbsd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/netbsd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/os2$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/os2$(DependSuffix)
	$(RM) $(IntermediateDirectory)/os2$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osx$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osx$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osx$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/read$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/read$(DependSuffix)
	$(RM) $(IntermediateDirectory)/read$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sector$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sector$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/solaris$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/solaris$(DependSuffix)
	$(RM) $(IntermediateDirectory)/solaris$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/track$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/track$(DependSuffix)
	$(RM) $(IntermediateDirectory)/track$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/utf8$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/utf8$(DependSuffix)
	$(RM) $(IntermediateDirectory)/utf8$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/util$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/util$(DependSuffix)
	$(RM) $(IntermediateDirectory)/util$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aspi32$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aspi32$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aspi32$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/win32$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/win32$(DependSuffix)
	$(RM) $(IntermediateDirectory)/win32$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/win32_ioctl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/win32_ioctl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/win32_ioctl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freebsd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freebsd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freebsd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freebsd_cam$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freebsd_cam$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freebsd_cam$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/freebsd_ioctl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/freebsd_ioctl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/freebsd_ioctl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bincue$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bincue$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bincue$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cdrdao$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cdrdao$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cdrdao$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nrg$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nrg$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nrg$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


