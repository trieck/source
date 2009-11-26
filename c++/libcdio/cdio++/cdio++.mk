##
## Auto Generated makefile, please do not edit
##
WXWIN:=D:\wxWidgets-2.8.10
WXCFG:=gcc_dll\mswu
ProjectName:=cdio++

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "D:\source\c++\libcdio"
ProjectPath            := "D:\source\c++\libcdio\cdio++"
CurrentFileName        :=
CurrentFulePath        :=
CurrentFileFullPath    :=
User                   :=trieck
Date                   :=11/25/09
CodeLitePath           :="d:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=$(PreprocessorSwitch)HAVE_CONFIG_H $(PreprocessorSwitch)EXTERNAL_LIBCDIO_CONFIG_H 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../" "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/cdio$(ObjectSuffix) $(IntermediateDirectory)/devices$(ObjectSuffix) $(IntermediateDirectory)/iso9660$(ObjectSuffix) 

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
$(IntermediateDirectory)/cdio$(ObjectSuffix): ../../../../libcdio/lib/cdio++/cdio.cpp $(IntermediateDirectory)/cdio$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/cdio++/cdio.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/cdio$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cdio$(DependSuffix): ../../../../libcdio/lib/cdio++/cdio.cpp
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/cdio$(ObjectSuffix) -MF$(IntermediateDirectory)/cdio$(DependSuffix) -MM "D:/libcdio/lib/cdio++/cdio.cpp"

$(IntermediateDirectory)/devices$(ObjectSuffix): ../../../../libcdio/lib/cdio++/devices.cpp $(IntermediateDirectory)/devices$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/cdio++/devices.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/devices$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/devices$(DependSuffix): ../../../../libcdio/lib/cdio++/devices.cpp
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/devices$(ObjectSuffix) -MF$(IntermediateDirectory)/devices$(DependSuffix) -MM "D:/libcdio/lib/cdio++/devices.cpp"

$(IntermediateDirectory)/iso9660$(ObjectSuffix): ../../../../libcdio/lib/cdio++/iso9660.cpp $(IntermediateDirectory)/iso9660$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "D:/libcdio/lib/cdio++/iso9660.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/iso9660$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/iso9660$(DependSuffix): ../../../../libcdio/lib/cdio++/iso9660.cpp
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/iso9660$(ObjectSuffix) -MF$(IntermediateDirectory)/iso9660$(DependSuffix) -MM "D:/libcdio/lib/cdio++/iso9660.cpp"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/cdio$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cdio$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/devices$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/devices$(DependSuffix)
	$(RM) $(IntermediateDirectory)/devices$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/iso9660$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/iso9660$(DependSuffix)
	$(RM) $(IntermediateDirectory)/iso9660$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


