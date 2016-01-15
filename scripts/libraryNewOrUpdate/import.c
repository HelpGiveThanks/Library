libraryNewOrUpdate: import
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::backup; "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" ]
Cut [ backup::backup ]
[ Select ]
#2 open file and determine its location (path) then close it after its location has been pasted using that file's open script into the main
data file
#file is unknown so user is given the opportunity to point the database to the backup copy of their choice
Go to Layout [ “defaultSetup” (tempSetup) ]
Open File [ <unknown> ]
If [ Get (LastError) = 1 ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#Make sure the file has been opened by this script.
Go to Layout [ “backup” (backup) ]
Paste [ backup::backup ]
[ Select; No style ]
If [ "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" = backup::backup ]
Show Custom Dialog [ Message: "Close the selected library. Then click update again to add its records to this updated version
of the library application."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $filepath; Value:backup::backup ]
#
#
#Test Section Records
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Show All Records
Import Records [ Source: “$filepath”; Target: “tagTestSubjectLocation”; Method: Add; Character Set: “Unicode”; Field Mapping: Source
field 1 import to tagTestSubjectLocation::knode
Source field 2 import to tagTestSubjectLocation::kfocus
Source field 3 import to tagTestSubjectLocation::_LtestSubjectLocation
Source field 4 import to tagTestSubjectLocation::kfocusAttribute1
Source field 5 import to tagTestSubjectLocation::focusName
Source field 6 import to tagTestSubjectLocation::inUse
Source field 7 import to tagTestSubjectLocation::order
Source field 8 import to tagTestSubjectLocation::TimeStart
Source field 9 import to tagTestSubjectLocation::TimeTotal
Source field 10 import to tagTestSubjectLocation::_number
Source field 11 import to tagTestSubjectLocation::kfocusAttribute2
Source field 12 import to tagTestSubjectLocation::ksection
Source field 13 import to tagTestSubjectLocation::reportNumber
Source field 14 import to tagTestSubjectLocation::kRecordCreatorNode ]
[ No dialog ]
#
#
#Test Records
Go to Layout [ “tableTest” (test) ]
Show All Records
Import Records [ Source: “$filepath”; Target: “test”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import to
test::_Ltest
Source field 2 import to test::ktestGroup
Source field 3 import to test::_number
Source field 4 import to test::kcfocusALL
Source field 5 import to test::testName
Source field 6 import to test::order
Source field 7 import to test::retire
Source field 8 import to test::kgtester
Source field 9 import to test::glocationNameGlobal
Source field 10 import to test::gcontactNameGlobal
Source field 11 import to test::kgaudienceLocation
Source field 12 import to test::gprogressGlobal
Source field 13 import to test::ksection
Source field 14 import to test::kgreportNumber
Source field 15 import to test::mtestGroup
Source field 16 import to test::ktestItemList
Source field 17 import to test::rule
Source field 18 import to test::kRecordCreatorNode
Source field 19 import to test::kRecordModifierNode
Source field 20 import to test::RecordModifyDate
Source field 21 import to test::testNameRevert ]
[ No dialog ]
#
#
#TestLearn Records
Go to Layout [ “tableTestLearn” (testlearn) ]
Show All Records
Import Records [ Source: “$filepath”; Target: “testlearn”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import
to testlearn::_Ltestlearn
Source field 2 import to testlearn::ktestSubject
Source field 3 import to testlearn::_Number
Source field 4 import to testlearn::ktest
Source field 5 import to testlearn::Caption
Source field 6 import to testlearn::Picture
Source field 7 import to testlearn::Location
Source field 8 import to testlearn::inUse
Source field 9 import to testlearn::kaudienceLocation
Source field 10 import to testlearn::InspectionItemCount
Source field 11 import to testlearn::CheckboxCaption
Source field 12 import to testlearn::recordnumberglobal
Source field 13 import to testlearn::recordcountglobal
Source field 14 import to testlearn::InspectionItemCountLocation
Source field 15 import to testlearn::OK
Source field 16 import to testlearn::kcsection
Source field 17 import to testlearn::kshowReferencedMedia
Source field 18 import to testlearn::TimeStart
Source field 19 import to testlearn::TimeStop
Source field 20 import to testlearn::TimeTotal
Source field 21 import to testlearn::kreportNumber
Source field 22 import to testlearn::timestamp
Source field 24 import to testlearn::orderDiscovery
Source field 25 import to testlearn::kcKeywordOther
Source field 26 import to testlearn::kNodeOther
Source field 27 import to testlearn::kHealth
Source field 28 import to testlearn::kNodePrimary
Source field 29 import to testlearn::kmedium
Source field 30 import to testlearn::kcitation
Source field 31 import to testlearn::kfileLocation
Source field 32 import to testlearn::kfolderPath
Source field 33 import to testlearn::kKeywordPrimary
Source field 34 import to testlearn::OtherKeyWords
Source field 35 import to testlearn::NodeOthers
Source field 36 import to testlearn::URL
Source field 37 import to testlearn::filename
Source field 38 import to testlearn::kcreference
Source field 40 import to testlearn::filterFind
Source field 41 import to testlearn::kRecordCreatorNode
Source field 42 import to testlearn::kRecordModifierNode
Source field 43 import to testlearn::RecordModifyDate
Source field 44 import to testlearn::incomplete
Source field 46 import to testlearn::copyrightYear
Source field 47 import to testlearn::URLPubDate
Source field 48 import to testlearn::kcsample
Source field 49 import to testlearn::gkaudienceLocation
Source field 50 import to testlearn::kctest
Source field 51 import to testlearn::orderTest
Source field 52 import to testlearn::title
Source field 53 import to testlearn::kctestItem
Source field 54 import to testlearn::organEmailRecipient
Source field 55 import to testlearn::korgan
Source field 56 import to testlearn::kcopyist
Source field 57 import to testlearn::emailDate
Source field 59 import to testlearn::sampleCasePoint ]
[ No dialog ]
#
#
#Tag Records
Go to Layout [ “tableTag” (tagTable) ]
#
#Delete node tag record.
Enter Find Mode [ ]
Set Field [ tagTable::match; "node" ]
Delete Record/Request
#
Show All Records
Import Records [ Source: “$filepath”; Target: “tagTable”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field
Mapping: Source field 1 import to tagTable::kGroupOrTest
Source field 2 match with tagTable::_Ltag
Source field 3 import to tagTable::tag
Source field 4 import to tagTable::orderOrLock
Source field 5 import to tagTable::ksection
Source field 6 import to tagTable::_Number
Source field 7 import to tagTable::match
Source field 8 import to tagTable::tagSpelling
Source field 9 import to tagTable::kcsection
Source field 10 import to tagTable::Kpicture1
Source field 11 import to tagTable::notesOrHealth
Source field 12 import to tagTable::Ktitle1
Source field 13 import to tagTable::kfile
Source field 15 import to tagTable::Kpicture2
Source field 17 import to tagTable::Kpicture3
Source field 19 import to tagTable::Ktitle2
Source field 20 import to tagTable::Ktitle3
Source field 24 import to tagTable::kRecordCreatorNode
Source field 25 import to tagTable::kRecordModifierNode ]
[ No dialog ]
#
#
#Tag Group Records
Go to Layout [ “tableGroupTag” (groupTest) ]
#
#Delete the empty library section record.
Enter Find Mode [ ]
Set Field [ groupTest::match; "section" ]
Delete All Records
#
#Delete node group record.
Enter Find Mode [ ]
Set Field [ groupTest::match; "node" ]
Delete All Records
#
Show All Records
Import Records [ Source: “$filepath”; Target: “groupTest”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field
Mapping: Source field 1 match with groupTest::_Lgroup
Source field 2 import to groupTest::_Number
Source field 3 import to groupTest::match
Source field 4 import to groupTest::name
Source field 5 import to groupTest::ksection
Source field 6 import to groupTest::defaultSectionInfo
Source field 7 import to groupTest::testReportPicture
Source field 8 import to groupTest::CaptionORinuseCheck
Source field 9 import to groupTest::URLORHealth
Source field 10 import to groupTest::order
Source field 11 import to groupTest::nameSpelling
Source field 12 import to groupTest::kRecordCreatorNode
Source field 13 import to groupTest::kSectionCreatorNodesCreator
Source field 14 import to groupTest::aboutSection ]
[ No dialog ]
#
#
#Reference Records
Go to Layout [ “tableReference” (reference) ]
Show All Records
Import Records [ Source: “$filepath”; Target: “reference”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field
Mapping: Source field 1 import to reference::_Number
Source field 2 match with reference::_Lreference
Source field 3 import to reference::ktestSubject
Source field 4 import to reference::ktest
Source field 5 import to reference::kcsection
Source field 6 import to reference::knodePrimary
Source field 7 import to reference::pubYear
Source field 8 import to reference::URL
Source field 9 import to reference::URLdate
Source field 10 import to reference::Title
Source field 11 import to reference::korgan
Source field 12 import to reference::volumeNumber
Source field 13 import to reference::PubDate
Source field 14 import to reference::pageNumberRange
Source field 15 import to reference::kcopyist
Source field 16 import to reference::OrginalCitation
Source field 17 import to reference::kcopyrightType
Source field 18 import to reference::kHealth
Source field 19 import to reference::kmedium
Source field 20 import to reference::kkeywordOther
Source field 21 import to reference::kkeywordPrimary
Source field 22 import to reference::thoughtsNotesEtc
Source field 23 import to reference::kfolderpath
Source field 24 import to reference::fileName
Source field 27 import to reference::referenceNodes
Source field 28 import to reference::CopyrightYear
Source field 29 import to reference::kcopyrightHolder
Source field 30 import to reference::referenceDump
Source field 31 import to reference::knodeOther
Source field 32 import to reference::NodeOthers
Source field 33 import to reference::OtherKeyWords
Source field 34 import to reference::referenceNodesOLD
Source field 35 import to reference::filterFind
Source field 36 import to reference::picture
Source field 37 import to reference::kfileLocation
Source field 38 import to reference::rights
Source field 39 import to reference::mFileLocation
Source field 40 import to reference::kcitation
Source field 41 import to reference::incomplete
Source field 42 import to reference::lock
Source field 44 import to reference::kcreatorNode
Source field 45 import to reference::kmodifierNode
Source field 46 import to reference::modifyDate
Source field 48 import to reference::TimeRange
Source field 51 import to reference::createDate
Source field 52 import to reference::showInLearn
Source field 53 import to reference::library only
Source field 54 import to reference::URLdoi
Source field 55 import to reference::issueNumber
Source field 56 import to reference::publisherLocation
Source field 57 import to reference::compilationTitle
Source field 58 import to reference::compilationEditors
Source field 59 import to reference::kmedia
Source field 60 import to reference::kmediaType
Source field 61 import to reference::compilationNumberOfEditors
Source field 62 import to reference::pubYearMonthRange
Source field 63 import to reference::ISBN
Source field 64 import to reference::pubDateOther
Source field 65 import to reference::bookChapter
Source field 66 import to reference::letterDate
Source field 67 import to reference::compilationAbbr
Source field 68 import to reference::emailRecipient
Source field 69 import to reference::conferenceIntroWords
Source field 70 import to reference::conferenceTitle
Source field 71 import to reference::conferenceSubTitle
Source field 72 import to reference::conferenceLocation
Source field 73 import to reference::conferenceDate
Source field 74 import to reference::conferenceGroupName
Source field 75 import to reference::TypeOfMediumOther
Source field 76 import to reference::GovernmentDocInfo
Source field 77 import to reference::governmentAuthor
Source field 78 import to reference::ISSN
Source field 79 import to reference::publisherTypeAlternative
Source field 80 import to reference::copyrightOtherHolder
Source field 81 import to reference::publisherTypeOther
Source field 82 import to reference::pageNumberOther
Source field 83 import to reference::dissertationThesisUniversity
Source field 87 import to reference::showMedia ]
[ No dialog ]
#
#
#Report Records
Go to Layout [ “tableReport” (report) ]
Show All Records
Import Records [ Source: “$filepath”; Target: “report”; Method: Add; Character Set: “Unicode”; Field Mapping: Source field 1 import to
report::_Lreport
Source field 2 import to report::_Number
Source field 3 import to report::ktestSubject
Source field 4 import to report::_kfContactGeography
Source field 5 import to report::general_info
Source field 6 import to report::ktest
Source field 7 import to report::krecommendation
Source field 8 import to report::order
Source field 9 import to report::Picture
Source field 10 import to report::kthingRecommendationID
Source field 11 import to report::kgeneralSpecificItemRecommendationID
Source field 12 import to report::_kfPhoto
Source field 13 import to report::_kfContactGeography2
Source field 14 import to report::_kfContactGeography3
Source field 15 import to report::_kfContactGeography4
Source field 16 import to report::_kfContactGeography5
Source field 17 import to report::PictureCaption
Source field 18 import to report::textMain
Source field 19 import to report::textPhotoRow1
Source field 20 import to report::pagenumberItem
Source field 21 import to report::CurrentRecord
Source field 22 import to report::_kfPhoto2
Source field 23 import to report::_kfPhoto3
Source field 24 import to report::_kfPhoto4
Source field 25 import to report::pagenumberTheme
Source field 26 import to report::TOC
Source field 27 import to report::TOCnumbers
Source field 28 import to report::ReportCover
Source field 29 import to report::ReportPDFtitle
Source field 30 import to report::kreportNumber
Source field 31 import to report::ksection
Source field 32 import to report::kRecordCreatorNode
Source field 33 import to report::kRecordModifierNode
Source field 34 import to report::RecordModifyDate
Source field 35 import to report::khealth
Source field 36 import to report::textPhotoRow2 ]
[ No dialog ]
#
Set Field [ backup::backup; "" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “defaultNode1” (tagMenus) ]
// Perform Script [ “defaultNodeMenu” ]
Select Window [ Name: "Setup"; Current file ]
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Set Field [ backup::backup; "" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
#
Set Variable [ $$import; Value:1 ]
#
January 14, ଘ౮28 21:57:11 Library.fp7 - import -1-
