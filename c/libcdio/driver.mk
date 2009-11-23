##
## Auto Generated makefile, please do not edit
##
ProjectName:=driver

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "D:\source\c\libcdio"
ProjectPath            := "D:\source\c\libcdio"
CurrentFileName        :=
CurrentFulePath        :=
CurrentFileFullPath    :=
User                   :=trieck
Date                   :=11/22/09
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
IncludePath            := "$(IncludeSwitch)D:/MinGW/include"  "$(IncludeSwitch)." "$(IncludeSwitch)D:/libcdio/MSVC" "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" "$(IncludeSwitch).." "$(IncludeSwitch)D:/libcdio/MSVC" "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" 
RcIncludePath          :=
Libs                   :=
LibPath                :="$(LibraryPathSwitch)D:/MinGW/Lib"  "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/util$(ObjectSuffix) $(IntermediateDirectory)/utf8$(ObjectSuffix) $(IntermediateDirectory)/track$(ObjectSuffix) $(IntermediateDirectory)/sector$(ObjectSuffix) $(IntermediateDirectory)/read$(ObjectSuffix) $(IntermediateDirectory)/netbsd$(ObjectSuffix) $(IntermediateDirectory)/mmc$(ObjectSuffix) $(IntermediateDirectory)/logging$(ObjectSuffix) $(IntermediateDirectory)/image_common$(ObjectSuffix) $(IntermediateDirectory)/ds$(ObjectSuffix) \
	$(IntermediateDirectory)/disc$(ObjectSuffix) $(IntermediateDirectory)/device$(ObjectSuffix) $(IntermediateDirectory)/cdtext$(ObjectSuffix) $(IntermediateDirectory)/cdio$(ObjectSuffix) $(IntermediateDirectory)/cd_types$(ObjectSuffix) $(IntermediateDirectory)/bsdi$(ObjectSuffix) $(IntermediateDirectory)/audio$(ObjectSuffix) $(IntermediateDirectory)/_cdio_stream$(ObjectSuffix) $(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix) $(IntermediateDirectory)/_cdio_generic$(ObjectSuffix) \
	

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
$(IntermediateDirectory)/util$(ObjectSuffix): ../../../libcdio/lib/driver/util.c $(IntermediateDirectory)/util$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/util.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/util$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util$(DependSuffix): ../../../libcdio/lib/driver/util.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/util$(ObjectSuffix) -MF$(IntermediateDirectory)/util$(DependSuffix) -MM "D:/libcdio/lib/driver/util.c"

$(IntermediateDirectory)/utf8$(ObjectSuffix): ../../../libcdio/lib/driver/utf8.c $(IntermediateDirectory)/utf8$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/utf8.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/utf8$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utf8$(DependSuffix): ../../../libcdio/lib/driver/utf8.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/utf8$(ObjectSuffix) -MF$(IntermediateDirectory)/utf8$(DependSuffix) -MM "D:/libcdio/lib/driver/utf8.c"

$(IntermediateDirectory)/track$(ObjectSuffix): ../../../libcdio/lib/driver/track.c $(IntermediateDirectory)/track$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/track.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/track$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/track$(DependSuffix): ../../../libcdio/lib/driver/track.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/track$(ObjectSuffix) -MF$(IntermediateDirectory)/track$(DependSuffix) -MM "D:/libcdio/lib/driver/track.c"

$(IntermediateDirectory)/sector$(ObjectSuffix): ../../../libcdio/lib/driver/sector.c $(IntermediateDirectory)/sector$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/sector.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sector$(DependSuffix): ../../../libcdio/lib/driver/sector.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sector$(ObjectSuffix) -MF$(IntermediateDirectory)/sector$(DependSuffix) -MM "D:/libcdio/lib/driver/sector.c"

$(IntermediateDirectory)/read$(ObjectSuffix): ../../../libcdio/lib/driver/read.c $(IntermediateDirectory)/read$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/read.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/read$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/read$(DependSuffix): ../../../libcdio/lib/driver/read.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/read$(ObjectSuffix) -MF$(IntermediateDirectory)/read$(DependSuffix) -MM "D:/libcdio/lib/driver/read.c"

$(IntermediateDirectory)/netbsd$(ObjectSuffix): ../../../libcdio/lib/driver/netbsd.c $(IntermediateDirectory)/netbsd$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/netbsd.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/netbsd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/netbsd$(DependSuffix): ../../../libcdio/lib/driver/netbsd.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/netbsd$(ObjectSuffix) -MF$(IntermediateDirectory)/netbsd$(DependSuffix) -MM "D:/libcdio/lib/driver/netbsd.c"

$(IntermediateDirectory)/mmc$(ObjectSuffix): ../../../libcdio/lib/driver/mmc.c $(IntermediateDirectory)/mmc$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/mmc.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/mmc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mmc$(DependSuffix): ../../../libcdio/lib/driver/mmc.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/mmc$(ObjectSuffix) -MF$(IntermediateDirectory)/mmc$(DependSuffix) -MM "D:/libcdio/lib/driver/mmc.c"

$(IntermediateDirectory)/logging$(ObjectSuffix): ../../../libcdio/lib/driver/logging.c $(IntermediateDirectory)/logging$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/logging.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/logging$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/logging$(DependSuffix): ../../../libcdio/lib/driver/logging.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/logging$(ObjectSuffix) -MF$(IntermediateDirectory)/logging$(DependSuffix) -MM "D:/libcdio/lib/driver/logging.c"

$(IntermediateDirectory)/image_common$(ObjectSuffix): ../../../libcdio/lib/driver/image_common.c $(IntermediateDirectory)/image_common$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/image_common.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/image_common$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/image_common$(DependSuffix): ../../../libcdio/lib/driver/image_common.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/image_common$(ObjectSuffix) -MF$(IntermediateDirectory)/image_common$(DependSuffix) -MM "D:/libcdio/lib/driver/image_common.c"

$(IntermediateDirectory)/ds$(ObjectSuffix): ../../../libcdio/lib/driver/ds.c $(IntermediateDirectory)/ds$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/ds.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ds$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ds$(DependSuffix): ../../../libcdio/lib/driver/ds.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ds$(ObjectSuffix) -MF$(IntermediateDirectory)/ds$(DependSuffix) -MM "D:/libcdio/lib/driver/ds.c"

$(IntermediateDirectory)/disc$(ObjectSuffix): ../../../libcdio/lib/driver/disc.c $(IntermediateDirectory)/disc$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/disc.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/disc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/disc$(DependSuffix): ../../../libcdio/lib/driver/disc.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/disc$(ObjectSuffix) -MF$(IntermediateDirectory)/disc$(DependSuffix) -MM "D:/libcdio/lib/driver/disc.c"

$(IntermediateDirectory)/device$(ObjectSuffix): ../../../libcdio/lib/driver/device.c $(IntermediateDirectory)/device$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/device.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/device$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/device$(DependSuffix): ../../../libcdio/lib/driver/device.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/device$(ObjectSuffix) -MF$(IntermediateDirectory)/device$(DependSuffix) -MM "D:/libcdio/lib/driver/device.c"

$(IntermediateDirectory)/cdtext$(ObjectSuffix): ../../../libcdio/lib/driver/cdtext.c $(IntermediateDirectory)/cdtext$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/cdtext.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cdtext$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cdtext$(DependSuffix): ../../../libcdio/lib/driver/cdtext.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cdtext$(ObjectSuffix) -MF$(IntermediateDirectory)/cdtext$(DependSuffix) -MM "D:/libcdio/lib/driver/cdtext.c"

$(IntermediateDirectory)/cdio$(ObjectSuffix): ../../../libcdio/lib/driver/cdio.c $(IntermediateDirectory)/cdio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/cdio.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cdio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cdio$(DependSuffix): ../../../libcdio/lib/driver/cdio.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cdio$(ObjectSuffix) -MF$(IntermediateDirectory)/cdio$(DependSuffix) -MM "D:/libcdio/lib/driver/cdio.c"

$(IntermediateDirectory)/cd_types$(ObjectSuffix): ../../../libcdio/lib/driver/cd_types.c $(IntermediateDirectory)/cd_types$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/cd_types.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cd_types$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cd_types$(DependSuffix): ../../../libcdio/lib/driver/cd_types.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cd_types$(ObjectSuffix) -MF$(IntermediateDirectory)/cd_types$(DependSuffix) -MM "D:/libcdio/lib/driver/cd_types.c"

$(IntermediateDirectory)/bsdi$(ObjectSuffix): ../../../libcdio/lib/driver/bsdi.c $(IntermediateDirectory)/bsdi$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/bsdi.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/bsdi$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bsdi$(DependSuffix): ../../../libcdio/lib/driver/bsdi.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/bsdi$(ObjectSuffix) -MF$(IntermediateDirectory)/bsdi$(DependSuffix) -MM "D:/libcdio/lib/driver/bsdi.c"

$(IntermediateDirectory)/audio$(ObjectSuffix): ../../../libcdio/lib/driver/audio.c $(IntermediateDirectory)/audio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/audio.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/audio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/audio$(DependSuffix): ../../../libcdio/lib/driver/audio.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/audio$(ObjectSuffix) -MF$(IntermediateDirectory)/audio$(DependSuffix) -MM "D:/libcdio/lib/driver/audio.c"

$(IntermediateDirectory)/_cdio_stream$(ObjectSuffix): ../../../libcdio/lib/driver/_cdio_stream.c $(IntermediateDirectory)/_cdio_stream$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/_cdio_stream.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/_cdio_stream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/_cdio_stream$(DependSuffix): ../../../libcdio/lib/driver/_cdio_stream.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/_cdio_stream$(ObjectSuffix) -MF$(IntermediateDirectory)/_cdio_stream$(DependSuffix) -MM "D:/libcdio/lib/driver/_cdio_stream.c"

$(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix): ../../../libcdio/lib/driver/_cdio_stdio.c $(IntermediateDirectory)/_cdio_stdio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/_cdio_stdio.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/_cdio_stdio$(DependSuffix): ../../../libcdio/lib/driver/_cdio_stdio.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix) -MF$(IntermediateDirectory)/_cdio_stdio$(DependSuffix) -MM "D:/libcdio/lib/driver/_cdio_stdio.c"

$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix): ../../../libcdio/lib/driver/_cdio_generic.c $(IntermediateDirectory)/_cdio_generic$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/driver/_cdio_generic.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/_cdio_generic$(DependSuffix): ../../../libcdio/lib/driver/_cdio_generic.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/_cdio_generic$(ObjectSuffix) -MF$(IntermediateDirectory)/_cdio_generic$(DependSuffix) -MM "D:/libcdio/lib/driver/_cdio_generic.c"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/util$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/util$(DependSuffix)
	$(RM) $(IntermediateDirectory)/util$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/utf8$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/utf8$(DependSuffix)
	$(RM) $(IntermediateDirectory)/utf8$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/track$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/track$(DependSuffix)
	$(RM) $(IntermediateDirectory)/track$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sector$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sector$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/read$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/read$(DependSuffix)
	$(RM) $(IntermediateDirectory)/read$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/netbsd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/netbsd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/netbsd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mmc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mmc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mmc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/logging$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/logging$(DependSuffix)
	$(RM) $(IntermediateDirectory)/logging$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/image_common$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/image_common$(DependSuffix)
	$(RM) $(IntermediateDirectory)/image_common$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ds$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ds$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ds$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/disc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/disc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/disc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/device$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/device$(DependSuffix)
	$(RM) $(IntermediateDirectory)/device$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cdtext$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cdtext$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cdtext$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cd_types$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cd_types$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cd_types$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/bsdi$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/bsdi$(DependSuffix)
	$(RM) $(IntermediateDirectory)/bsdi$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/audio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/audio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/audio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stdio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stdio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_stdio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_generic$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_generic$(DependSuffix)
	$(RM) $(IntermediateDirectory)/_cdio_generic$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


