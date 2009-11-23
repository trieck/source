##
## Auto Generated makefile, please do not edit
##
ProjectName:=iso9660

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "D:\source\c\libcdio"
ProjectPath            := "D:\source\c\libcdio\iso9660"
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
Preprocessors          :=$(PreprocessorSwitch)HAVE_CONFIG_H $(PreprocessorSwitch)EXTERNAL_LIBCDIO_CONFIG_H $(PreprocessorSwitch)HAVE_CONFIG_H $(PreprocessorSwitch)EXTERNAL_LIBCDIO_CONFIG_H 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            := "$(IncludeSwitch)D:/MinGW/include"  "$(IncludeSwitch)." "$(IncludeSwitch)../" "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" "$(IncludeSwitch)." "$(IncludeSwitch)D:/libcdio/include" "$(IncludeSwitch)D:/libcdio/lib/driver" 
RcIncludePath          :=
Libs                   :=
LibPath                :="$(LibraryPathSwitch)D:/MinGW/Lib"  "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/iso9660$(ObjectSuffix) $(IntermediateDirectory)/iso9660_fs$(ObjectSuffix) $(IntermediateDirectory)/rock$(ObjectSuffix) $(IntermediateDirectory)/xa$(ObjectSuffix) 

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
$(IntermediateDirectory)/iso9660$(ObjectSuffix): /libcdio/lib/iso9660/iso9660.c $(IntermediateDirectory)/iso9660$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "d:/libcdio/lib/iso9660/iso9660.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/iso9660$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/iso9660$(DependSuffix): /libcdio/lib/iso9660/iso9660.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/iso9660$(ObjectSuffix) -MF$(IntermediateDirectory)/iso9660$(DependSuffix) -MM "d:/libcdio/lib/iso9660/iso9660.c"

$(IntermediateDirectory)/iso9660_fs$(ObjectSuffix): /libcdio/lib/iso9660/iso9660_fs.c $(IntermediateDirectory)/iso9660_fs$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "d:/libcdio/lib/iso9660/iso9660_fs.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/iso9660_fs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/iso9660_fs$(DependSuffix): /libcdio/lib/iso9660/iso9660_fs.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/iso9660_fs$(ObjectSuffix) -MF$(IntermediateDirectory)/iso9660_fs$(DependSuffix) -MM "d:/libcdio/lib/iso9660/iso9660_fs.c"

$(IntermediateDirectory)/rock$(ObjectSuffix): /libcdio/lib/iso9660/rock.c $(IntermediateDirectory)/rock$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "d:/libcdio/lib/iso9660/rock.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/rock$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rock$(DependSuffix): /libcdio/lib/iso9660/rock.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/rock$(ObjectSuffix) -MF$(IntermediateDirectory)/rock$(DependSuffix) -MM "d:/libcdio/lib/iso9660/rock.c"

$(IntermediateDirectory)/xa$(ObjectSuffix): /libcdio/lib/iso9660/xa.c $(IntermediateDirectory)/xa$(DependSuffix)
	@makedir "./Debug"
	$(CompilerName) $(SourceSwitch) "d:/libcdio/lib/iso9660/xa.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/xa$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/xa$(DependSuffix): /libcdio/lib/iso9660/xa.c
	@makedir "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/xa$(ObjectSuffix) -MF$(IntermediateDirectory)/xa$(DependSuffix) -MM "d:/libcdio/lib/iso9660/xa.c"

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/iso9660$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/iso9660$(DependSuffix)
	$(RM) $(IntermediateDirectory)/iso9660$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/iso9660_fs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/iso9660_fs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/iso9660_fs$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/rock$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/rock$(DependSuffix)
	$(RM) $(IntermediateDirectory)/rock$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/xa$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/xa$(DependSuffix)
	$(RM) $(IntermediateDirectory)/xa$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*$(DependSuffix)


