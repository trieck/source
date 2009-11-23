##
## Auto Generated makefile, please do not edit
##
ProjectName:=iso_read

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "D:\source\c\libcdio"
ProjectPath            := "D:\source\c\libcdio\iso_read"
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)HAVE_CONFIG_H $(PreprocessorSwitch)EXTERNAL_LIBCDIO_CONFIG_H 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            := "$(IncludeSwitch)D:/MinGW/include"  "$(IncludeSwitch)." "$(IncludeSwitch)../" "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)iso9660 $(LibrarySwitch)driver 
LibPath                :="$(LibraryPathSwitch)D:/MinGW/Lib"  "$(LibraryPathSwitch)." "$(LibraryPathSwitch)../driver/./Debug" "$(LibraryPathSwitch)../iso9660/./Debug" 


Objects=$(IntermediateDirectory)/iso-read$(ObjectSuffix) $(IntermediateDirectory)/util$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@makedir $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@makedir "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/iso-read$(ObjectSuffix): ../../../../libcdio/src/iso-read.c $(IntermediateDirectory)/iso-read$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/src/iso-read.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/iso-read$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/iso-read$(DependSuffix): ../../../../libcdio/src/iso-read.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/iso-read$(ObjectSuffix) -MF$(IntermediateDirectory)/iso-read$(DependSuffix) -MM "D:/libcdio/src/iso-read.c"

$(IntermediateDirectory)/util$(ObjectSuffix): ../../../../libcdio/src/util.c $(IntermediateDirectory)/util$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/src/util.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/util$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util$(DependSuffix): ../../../../libcdio/src/util.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/util$(ObjectSuffix) -MF$(IntermediateDirectory)/util$(DependSuffix) -MM "D:/libcdio/src/util.c"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/iso-read$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/iso-read$(DependSuffix)
	$(RM) $(IntermediateDirectory)/iso-read$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/util$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/util$(DependSuffix)
	$(RM) $(IntermediateDirectory)/util$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe

-include $(IntermediateDirectory)/*$(DependSuffix)


