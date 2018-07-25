July 24, 2018 17:35:03 Library.fmp12 - newLibraryStep3B_importLibraryIntoEmptiedLibrary -1-
libraryNewOrImport: newLibraryStep3B_importLibraryIntoEmptiedLibrary
#
#
#PURPOSE: This script is step 3B of a three step
#process for creating a copy of the current
#library file for use as a new empty library or
#as an upgrade library file.
#— Admin access required. —
# Step 1) Creates a copy of current library.
#A copy not a clone must be created because some
#records are neccessary to running the Library and
#are removed when cloning the Library.
#— Admin access required. —
# Step 2) When user opens the copy that this
#script creates, the createEmptyLibrary script
#erases the copy's records preparing it to
#become an empty library or an upgrade file
#of the library ready for sharing.
#— Regular user access —
# Step 3 A) Create new library name
#and node records and begin to use the library
#file as a new library, OR B) Import records
#from an older library and use library file as an
#upgrade library file.
#
#
#BEGIN STEP 3B: Upgrade (import) old library.
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Inform user crashing issue when importing.
Show Custom Dialog [ Message: "On some imports FileMaker crashes. So, makes sure you have a duplicate of this Empty Library
file before proceeding (cancel and duplicate if you don't)."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Show Custom Dialog [ Message: "When you are ready to decide what to do with this empty library re-open it. This library will
now close."; Default Button: “OK”, Commit: “Yes” ]
Close Window [ Current Window ]
Exit Script [ ]
End If
Show Custom Dialog [ Message: "Do not be discouraged if FileMaker crashes several times in a row. Eventually, it will work. Always
delete the crashed library, and use a fresh copy for your import."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit:
“No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Show Custom Dialog [ Message: "When you are ready to decide what to do with this empty library re-open it. This library will
now close."; Default Button: “OK”, Commit: “Yes” ]
Close Window [ Current Window ]
Exit Script [ ]
End If
Show Custom Dialog [ Message: "If it does crash, delete the crashed library file, and try again."; Default Button: “OK”, Commit: “Yes”;
Button 2: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Show Custom Dialog [ Message: "When you are ready to decide what to do with this empty library re-open it. This library will
now close."; Default Button: “OK”, Commit: “Yes” ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#Get path of library that user wants to import
#files from by generating this code and
#cuting it using the computer's clipboard so
#it can be pasted by the library the user is now
#opening (the one they want to import files
#from).
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::backup; "0update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" ]
#
#Cut instead of copy, saves the step of erasing
#this code from the current file, as the cut
#command both copies and erases the code.
Cut [ backup::backup ]
[ Select ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
#
#Ask the user what file they want to
#import from. Because it is an (unknown) file,
#the user will be prompted to select this file.
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
Open File [ <unknown> ]
#
#If the user cancels the file selection process,
#then exit this script, and close the library.
#The library cannot be used until the user
#either imports an old library's records into it
#or sets it up as a new library.
If [ Get (LastError) = 1 ]
Show Custom Dialog [ Message: "When you are ready to decide what to do with this empty library re-open it. This library will
now close."; Default Button: “OK”, Commit: “Yes” ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#Make sure the file the user selected to import
#from was opened and its filepath copied. If it
#was already open, then this script did not
#open it and its startDatabase script did not
#just run and insert this code, which would
#have resulted in its filepath being copied by
#the computer's clipboard. Thus the
#computer's clipboard will still contain the
#copy-filepath code, instead of the file's
#filepath.
Go to Layout [ “backup” (backup) ]
Paste [ backup::backup ]
[ Select; No style ]
If [ "0update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" = backup::backup ]
#
#Tell the user the import failed and how to
#succeed. Then restart the library to all the
#user to try again.
Show Custom Dialog [ Message: "Close the library whose records you wish to import and try the import process again."; Default
Button: “OK”, Commit: “Yes” ]
Set Field [ backup::backup; "" ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
Perform Script [ “startDatabase” ]
Exit Script [ ]
End If
#
#If the computer's clipboard contains a
#filepath, then proceed with the import.
Set Variable [ $filepath; Value:backup::backup ]
#
#
#1) Import test section records.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Import Records [ Source: “$filepath”; Target: “testSectionCreatedFromATemplate”; Method: Add; Character Set: “Unicode”; Field
Mapping: Source field 1 import to testSectionCreatedFromATemplate::ktestSubjectNode
Source field 2 import to testSectionCreatedFromATemplate::ksectionTemplate
Source field 3 import to testSectionCreatedFromATemplate::_LtestSection
Source field 4 import to testSectionCreatedFromATemplate::name
Source field 5 import to testSectionCreatedFromATemplate::inUse
Source field 6 import to testSectionCreatedFromATemplate::order
Source field 7 import to testSectionCreatedFromATemplate::_number
Source field 8 import to testSectionCreatedFromATemplate::klibrary
Source field 9 import to testSectionCreatedFromATemplate::reportNumber
Source field 10 import to testSectionCreatedFromATemplate::kcreatorNode
Source field 12 import to testSectionCreatedFromATemplate::creationDate
Source field 13 import to testSectionCreatedFromATemplate::creationTime ]
[ No dialog ]
#
#
#2) Import test subsection records.
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Import Records [ Source: “$filepath”; Target: “testSubsectionTemplate”; Method: Add; Character Set: “Unicode”; Field Mapping:
Source field 1 import to testSubsectionTemplate::_LtestSubsection
Source field 2 import to testSubsectionTemplate::ksubsectionGroup
Source field 3 import to testSubsectionTemplate::_number
Source field 4 import to testSubsectionTemplate::kcsections
Source field 5 import to testSubsectionTemplate::name
Source field 6 import to testSubsectionTemplate::order
Source field 7 import to testSubsectionTemplate::retire
Source field 8 import to testSubsectionTemplate::kgtestSubject
Source field 9 import to testSubsectionTemplate::gtestSectionNameGlobal
Source field 10 import to testSubsectionTemplate::gtestSubjectNameGlobal
Source field 11 import to testSubsectionTemplate::kgtestSection
Source field 12 import to testSubsectionTemplate::gprogressGlobal
Source field 13 import to testSubsectionTemplate::klibrary
Source field 14 import to testSubsectionTemplate::kgreportNumber
Source field 15 import to testSubsectionTemplate::mtestSubsection
Source field 16 import to testSubsectionTemplate::ktestItemGroup
Source field 17 import to testSubsectionTemplate::rule
Source field 18 import to testSubsectionTemplate::kcreatorNode
Source field 19 import to testSubsectionTemplate::kmodifierNode
Source field 20 import to testSubsectionTemplate::RecordModifyDate
Source field 21 import to testSubsectionTemplate::nameSpelling
Source field 22 import to testSubsectionTemplate::form ]
[ No dialog ]
#
#
#3) Import learn and test result records.
Go to Layout [ “tableTestLearn” (testlearn) ]
Import Records [ Source: “$filepath”; Target: “testlearn”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import
to testlearn::_Ltestlearn
Source field 2 import to testlearn::ktestSubject
Source field 3 import to testlearn::_Number
Source field 4 import to testlearn::ktestSubsection
Source field 5 import to testlearn::note
Source field 6 import to testlearn::picture
Source field 7 import to testlearn::subsectionCustomName
Source field 8 import to testlearn::kcInUseOnReportSubsection
Source field 9 import to testlearn::ktestSection
Source field 10 import to testlearn::countOfALLSubsectionsTestResults
Source field 11 import to testlearn::checkboxCaption
Source field 12 import to testlearn::recordnumberglobal
Source field 13 import to testlearn::recordcountglobal
Source field 14 import to testlearn::countOfONESubsectionsTestResults
Source field 15 import to testlearn::rateORgradeTestResult
Source field 16 import to testlearn::kclibrary
Source field 17 import to testlearn::kshowReferencedMedia
Source field 18 import to testlearn::kreportNumber
Source field 19 import to testlearn::timestamp
Source field 21 import to testlearn::orderTestResult
Source field 22 import to testlearn::kcKeywordOther
Source field 23 import to testlearn::kNodeOther
Source field 24 import to testlearn::kcopyright
Source field 25 import to testlearn::kNodePrimary
Source field 26 import to testlearn::kKeywordPrimary
Source field 27 import to testlearn::OtherKeyWords
Source field 28 import to testlearn::NodeOthers
Source field 29 import to testlearn::URL
Source field 30 import to testlearn::kcreference
Source field 32 import to testlearn::filterFind
Source field 33 import to testlearn::kRecordCreatorNode
Source field 34 import to testlearn::kRecordModifierNode
Source field 35 import to testlearn::dateModify
Source field 36 import to testlearn::incomplete
Source field 38 import to testlearn::copyrightYear
Source field 39 import to testlearn::kcbrainstorm
Source field 40 import to testlearn::kgtestSection
Source field 41 import to testlearn::kctestSubsectionInfo
Source field 42 import to testlearn::orderTestInformation
Source field 43 import to testlearn::kctestResultCheckedItems
Source field 45 import to testlearn::brainstormCasePoint
Source field 48 import to testlearn::pictureThumbnail ]
[ No dialog ]
#
#
#4) Import about library records.
Go to Layout [ “tableAboutLibrary” (aboutLibrary) ]
Import Records [ Source: “$filepath”; Target: “aboutLibrary”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1
import to aboutLibrary::_LaboutLibrary
Source field 2 import to aboutLibrary::_Number
Source field 3 import to aboutLibrary::URL
Source field 4 import to aboutLibrary::publicationDate
Source field 5 import to aboutLibrary::kcreatorNode
Source field 6 import to aboutLibrary::name
Source field 7 import to aboutLibrary::password
Source field 8 import to aboutLibrary::klibrary
Source field 9 import to aboutLibrary::version
Source field 13 import to aboutLibrary::creatorName
Source field 14 import to aboutLibrary::note ]
[ No dialog ]
#
#
#5) Import tag records.
Go to Layout [ “tableTag” (tagTable) ]
Import Records [ Source: “$filepath”; Target: “tagTable”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import
to tagTable::kGroupOrTest
Source field 2 import to tagTable::_Ltag
Source field 3 import to tagTable::tag
Source field 4 import to tagTable::orderOrLock
Source field 5 import to tagTable::textStyleOrCreatorNodeFlag
Source field 6 import to tagTable::_Number
Source field 7 import to tagTable::match
Source field 8 import to tagTable::tagSpelling
Source field 9 import to tagTable::Kpicture1
Source field 10 import to tagTable::notesOrCopyright
Source field 11 import to tagTable::Ktitle1
Source field 12 import to tagTable::kfileORkTestItemCreatorNode
Source field 14 import to tagTable::Kpicture2
Source field 16 import to tagTable::Kpicture3
Source field 18 import to tagTable::Ktitle2
Source field 19 import to tagTable::Ktitle3
Source field 23 import to tagTable::kRecordCreatorNode
Source field 24 import to tagTable::notesForKeyandNodeTags ]
[ No dialog ]
#
#
#6) Import tag group records.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Import Records [ Source: “$filepath”; Target: “testSubsectionGroup”; Method: Add; Character Set: “Unicode”; Field Mapping: Source
field 1 import to testSubsectionGroup::_Lgroup
Source field 2 import to testSubsectionGroup::_Number
Source field 3 import to testSubsectionGroup::match
Source field 4 import to testSubsectionGroup::name
Source field 5 import to testSubsectionGroup::klibrary
Source field 6 import to testSubsectionGroup::nameSpellingFORTestItemGroup
Source field 7 import to testSubsectionGroup::testReportPicture
Source field 8 import to testSubsectionGroup::ReportCaptionORLibraryCreatorName
Source field 9 import to testSubsectionGroup::URLOrCopyrightORUserLibraryVersion
Source field 10 import to testSubsectionGroup::orderOrLibraryType
Source field 11 import to testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup
Source field 12 import to testSubsectionGroup::kRecordCreatorNode
Source field 13 import to testSubsectionGroup::versionNumber ]
[ No dialog ]
#
#
#7) Import reference records.
#Make sure no locked reference copyright
#records are currently found, so that after the
#import when locked records are deleted, they
#are duplicates from the just imported library.
Go to Layout [ “tableReference” (reference) ]
Omit Multiple Records [ 999 ]
[ No dialog ]
Import Records [ Source: “$filepath”; Target: “reference”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import
to reference::_Number
Source field 2 import to reference::_Lreference
Source field 3 import to reference::ktestSubject
Source field 4 import to reference::ktest
Source field 5 import to reference::kclibrary
Source field 6 import to reference::knodePrimary
Source field 7 import to reference::publicationYearOrStuffOrderNumber
Source field 8 import to reference::URL
Source field 9 import to reference::URLdate
Source field 10 import to reference::Title
Source field 11 import to reference::kpublication
Source field 12 import to reference::volumeNumber
Source field 13 import to reference::PubDate
Source field 14 import to reference::pageNumberRange
Source field 15 import to reference::kpublisher
Source field 16 import to reference::OrginalCitation
Source field 17 import to reference::kcopyrightType
Source field 18 import to reference::kCopyright
Source field 19 import to reference::kmedium
Source field 20 import to reference::kkeywordOther
Source field 21 import to reference::kkeywordPrimary
Source field 22 import to reference::thoughtsNotesEtc
Source field 23 import to reference::kfolderpath
Source field 24 import to reference::fileName
Source field 26 import to reference::referenceNodes
Source field 27 import to reference::CopyrightYear
Source field 28 import to reference::kcopyrightHolder
Source field 29 import to reference::referenceDump
Source field 30 import to reference::knodeOther
Source field 31 import to reference::NodeOthers
Source field 32 import to reference::OtherKeyWords
Source field 33 import to reference::referenceNodesOLD
Source field 34 import to reference::filterFind
Source field 35 import to reference::picture
Source field 36 import to reference::kfileLocation
Source field 37 import to reference::rights
Source field 38 import to reference::mFileFolderMainXorOther
Source field 39 import to reference::kcitation
Source field 40 import to reference::incomplete
Source field 41 import to reference::lock
Source field 43 import to reference::kcreatorNode
Source field 44 import to reference::kmodifierNode
Source field 45 import to reference::modifyDate
Source field 47 import to reference::TimeRange
Source field 48 import to reference::createDate
Source field 49 import to reference::showInLearn
Source field 50 import to reference::publicLibraryLinks
Source field 51 import to reference::DOI
Source field 52 import to reference::issueNumber
Source field 53 import to reference::publisherLocation
Source field 54 import to reference::publicationTitle
Source field 55 import to reference::compilationEditors
Source field 56 import to reference::kisWhat
Source field 57 import to reference::kisON
Source field 58 import to reference::compilationNumberOfEditors
Source field 59 import to reference::publicationYearMonthRange
Source field 60 import to reference::ISBN
Source field 61 import to reference::pubDateOther
Source field 62 import to reference::bookChapter
Source field 63 import to reference::letterDate
Source field 64 import to reference::compilationAbbr
Source field 65 import to reference::emailRecipient
Source field 66 import to reference::conferenceIntroWords
Source field 67 import to reference::conferenceTitle
Source field 68 import to reference::conferenceSubTitle
Source field 69 import to reference::conferenceLocation
Source field 70 import to reference::conferenceDate
Source field 71 import to reference::otherIsOn
Source field 72 import to reference::GovernmentDocInfo
Source field 73 import to reference::governmentAuthor
Source field 74 import to reference::ISSN
Source field 75 import to reference::publisherTypeAlternative
Source field 76 import to reference::copyrightOtherHolder
Source field 77 import to reference::publisherTypeOther
Source field 78 import to reference::pageNumberOther
Source field 79 import to reference::dissertationThesisUniversity
Source field 83 import to reference::showMedia
Source field 84 import to reference::showMediaCode
Source field 85 import to reference::PictureFileSize
Source field 87 import to reference::pictureSourceSpeedLimit
Source field 88 import to reference::pictureThumbnail
Source field 91 import to reference::otherIsWhat ]
[ No dialog ]
#
#Now delete the imported lock copyright
#records, to insure the latests locked
#copyright records already in this file remain
#the only ones.
If [ Get (FoundCount) ≠ 0 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::lock; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
If [ reference::lock = "lock" ]
Delete Record/Request
[ No dialog ]
End If
Exit Loop If [ reference::lock ≠ "lock" ]
Exit Loop If [ Get (FoundCount) = 0 ]
End Loop
End If
#
#
#8) Import report records.
Go to Layout [ “tableReport” (report) ]
Import Records [ Source: “$filepath”; Target: “report”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import to
report::_Lreport
Source field 2 import to report::_Number
Source field 3 import to report::ktestSubject
Source field 4 import to report::kTestSubjectSection
Source field 5 import to report::general_info
Source field 6 import to report::ktestSubsection
Source field 7 import to report::kRecommendation1
Source field 8 import to report::order
Source field 9 import to report::Picture
Source field 10 import to report::kRecommendation2
Source field 11 import to report::kgeneralSpecificItemRecommendationID
Source field 12 import to report::kTag1
Source field 13 import to report::kTestSubjectSection2
Source field 14 import to report::kTestSubjectSection3
Source field 15 import to report::kTestSubjectSection4
Source field 16 import to report::kTestSubjectSection5
Source field 17 import to report::PictureCaptionInsteadOfPicture
Source field 18 import to report::note
Source field 19 import to report::textPhotoRow1
Source field 20 import to report::pagenumberItem
Source field 21 import to report::CurrentRecord
Source field 22 import to report::kTag2
Source field 23 import to report::kTag3
Source field 24 import to report::kTag4
Source field 25 import to report::pagenumberTheme
Source field 26 import to report::TOC
Source field 27 import to report::TOCnumbers
Source field 28 import to report::ReportCover
Source field 29 import to report::ReportPDFtitle
Source field 30 import to report::kreportNumber
Source field 31 import to report::klibrary
Source field 32 import to report::kRecordCreatorNode
Source field 33 import to report::kRecordModifierNode
Source field 34 import to report::RecordModifyDate
Source field 35 import to report::kcopyright
Source field 36 import to report::textPhotoRow2 ]
[ No dialog ]
#
#
#9) Import TEMP records.
Go to Layout [ “tableTemp” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
Import Records [ Source: “$filepath”; Target: “TEMP”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import to
TEMP::theme
Source field 2 import to TEMP::klibrary
Source field 3 import to TEMP::userLibraryName
Source field 4 import to TEMP::testSubsectionNameForSubject
Source field 5 import to TEMP::orderLocation
Source field 6 import to TEMP::orderMod1
Source field 7 import to TEMP::orderMod2
Source field 8 import to TEMP::reportNumber
Source field 9 import to TEMP::ktestItemSubsection
Source field 10 import to TEMP::ktestItemSubsectionOLD
Source field 11 import to TEMP::TimeStamp
Source field 12 import to TEMP::ktestSection
Source field 13 import to TEMP::ktestSubsection
Source field 14 import to TEMP::showFavorites
Source field 15 import to TEMP::kabout
Source field 16 import to TEMP::mtestSubsection
Source field 17 import to TEMP::DeleteMessageInTempWindow1
Source field 18 import to TEMP::mSwitch
Source field 19 import to TEMP::pageNumber
Source field 21 import to TEMP::import
Source field 22 import to TEMP::theme Copy
Source field 23 import to TEMP::newEvidenceListWindow
Source field 24 import to TEMP::EvidenceItemNameAndNumber
Source field 25 import to TEMP::sortKey
Source field 26 import to TEMP::sortNode
Source field 27 import to TEMP::sortPublisher
Source field 28 import to TEMP::sortMedium
Source field 29 import to TEMP::sortPath
Source field 30 import to TEMP::tagName
Source field 31 import to TEMP::testSubsectionName
Source field 32 import to TEMP::sortPublication
Source field 33 import to TEMP::sortCopyright
Source field 34 import to TEMP::sortCite
Source field 35 import to TEMP::layoutRtagN
Source field 36 import to TEMP::layoutRtagK
Source field 37 import to TEMP::layoutLtagK
Source field 38 import to TEMP::layoutLtagN
Source field 39 import to TEMP::sortRef
Source field 40 import to TEMP::DetailmoreORLessLayout
Source field 41 import to TEMP::kdefaultNodePrimary
Source field 42 import to TEMP::kdefaultCopyright
Source field 43 import to TEMP::kdefaultNodeOther
Source field 44 import to TEMP::DEFAULTNodeOtherNames
Source field 46 import to TEMP::DefaultmoreORLessLayoutNode
Source field 47 import to TEMP::layoutLmain
Source field 48 import to TEMP::sortBrainstorm
Source field 49 import to TEMP::tempListNode
Source field 50 import to TEMP::TLBrainstormSort
Source field 51 import to TEMP::TLTestSort
Source field 52 import to TEMP::sortTestSubsection
Source field 53 import to TEMP::kdefaultNodeTestSubject
Source field 55 import to TEMP::sortTestSection
Source field 56 import to TEMP::pulldownAttribute
Source field 57 import to TEMP::testHideFormTextItemsFTs
Source field 58 import to TEMP::userLocationName
Source field 59 import to TEMP::kctagTest
Source field 61 import to TEMP::mtestSection
Source field 62 import to TEMP::kcsubsectionSections
Source field 63 import to TEMP::sortTestItem
Source field 64 import to TEMP::mTestItemGroup
Source field 65 import to TEMP::addTestItemGroup
Source field 66 import to TEMP::ktestSubsectionName
Source field 67 import to TEMP::filePathLibraryToSwitchTo
Source field 68 import to TEMP::DEFAULTNodePrimaryName
Source field 69 import to TEMP::textORcheck
Source field 70 import to TEMP::mTag
Source field 71 import to TEMP::duplicateOtherKeywords
Source field 72 import to TEMP::kcbrainstorm
Source field 74 import to TEMP::primaryNodeIsLocked
Source field 75 import to TEMP::nodeLockedShow
Source field 76 import to TEMP::paste
Source field 77 import to TEMP::mCopyright
Source field 79 import to TEMP::Help
Source field 80 import to TEMP::helpName
Source field 81 import to TEMP::InventoryLibraryYN
Source field 82 import to TEMP::DEFAULTNodeTestSubjectName
Source field 83 import to TEMP::Message
Source field 84 import to TEMP::layoutLtagR
Source field 85 import to TEMP::layoutLtagL
Source field 86 import to TEMP::ReferenceFolder
Source field 88 import to TEMP::HelpRepetitionNumber
Source field 89 import to TEMP::HelpMessage
Source field 92 import to TEMP::textDateIntialTime
Source field 93 import to TEMP::DEFAULTSectionName
Source field 94 import to TEMP::kdefaultSectionTemplate
Source field 95 import to TEMP::passwordCheck
Source field 96 import to TEMP::userLibraryMainOrBranch
Source field 97 import to TEMP::DEFAULTprimaryNodeCopyrightGroup
Source field 98 import to TEMP::kdefaultTestSubjectCopyright
Source field 99 import to TEMP::ReferenceDump
Source field 100 import to TEMP::kdefaultNodePrimaryCreator
Source field 101 import to TEMP::primaryNodesCreatorNodeIsLocked
Source field 103 import to TEMP::copyrightCreatorsName
Source field 104 import to TEMP::testSubjectNodeIsLocked
Source field 105 import to TEMP::testSubsectionHideTextItems
Source field 106 import to TEMP::DeleteMessageInTempWindow2
Source field 107 import to TEMP::layoutTmain
Source field 109 import to TEMP::testAndReportMainWindowHeader
Source field 110 import to TEMP::testItemMenuShowTheWordLock
Source field 111 import to TEMP::userLibraryVersionNumber ]
[ No dialog ]
#
#
#Erase codes that trigger new
#library creation script steps.
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::backup; "" ]
Set Field [ backup::newLibrary; "" ]
#
#Complete import by restarting the library,
#loading up the imported data, telling the
#user to pick themselves as the primary node,
#and to select the copyright for new records.
# This variable will trigger these final steps
#found at the end of startDatabase script.
Set Variable [ $$import; Value:1 ]
Perform Script [ “startDatabase” ]
#
#END STEP 3B: Upgrade (import) old library.
#
#
