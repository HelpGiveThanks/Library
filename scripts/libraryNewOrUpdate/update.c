libraryNewOrUpdate: update
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::backup; "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" ]
Cut [ backup::backup ]
[ Select ]
#2 open ﬁle and determine its location (path) then close it after its location has been pasted using that ﬁle's open script into the main data ﬁle
#ﬁle is unknown so user is given the opportunity to point the database to the backup copy of their choice
Go to Layout [ “defaultSetup” (tempSetup) ]
Open File [ <unknown> ]
If [ Get (LastError) = 1 ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#Make sure the ﬁle has been opened by this script.
Go to Layout [ “backup” (backup) ]
Paste [ backup::backup ]
[ Select; No style ]
If [ "update439asdkc;liasdu;irejf.as.dkfupea;lksdfa,sm.eupqoiwendssasdeawsrre5o983498woeirf" = backup::backup ]
Show Custom Dialog [ Message: "Close the selected library. Then click update again to add its records to this updated version of the library application."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $ﬁlepath; Value:backup::backup ]
#
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “tagTestSubjectLocation”; Method: Add; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 import to tagTestSubjectLocation::knode
Source ﬁeld 2 import to tagTestSubjectLocation::kfocus
Source ﬁeld 3 import to tagTestSubjectLocation::_LtestSubjectLocation
Source ﬁeld 4 import to tagTestSubjectLocation::kfocusAttribute1
Source ﬁeld 5 import to tagTestSubjectLocation::focusName
Source ﬁeld 6 import to tagTestSubjectLocation::inUse
Source ﬁeld 7 import to tagTestSubjectLocation::order
Source ﬁeld 8 import to tagTestSubjectLocation::TimeStart
Source ﬁeld 9 import to tagTestSubjectLocation::TimeTotal
Source ﬁeld 10 import to tagTestSubjectLocation::_number
Source ﬁeld 11 import to tagTestSubjectLocation::kfocusAttribute2
Source ﬁeld 12 import to tagTestSubjectLocation::ksection
Source ﬁeld 13 import to tagTestSubjectLocation::reportNumber
Source ﬁeld 14 import to tagTestSubjectLocation::kRecordCreatorNode ]
[ No dialog ]
#
Go to Layout [ “tableTest” (test) ]
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “test”; Method: Add; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 import to test::_Ltest
Source ﬁeld 2 import to test::ktestGroup
Source ﬁeld 3 import to test::_number
Source ﬁeld 4 import to test::kcfocusALL
Source ﬁeld 5 import to test::testName
Source ﬁeld 6 import to test::order
Source ﬁeld 7 import to test::retire
Source ﬁeld 8 import to test::kgtester
Source ﬁeld 9 import to test::glocationNameGlobal
Source ﬁeld 10 import to test::gcontactNameGlobal
Source ﬁeld 11 import to test::kgaudienceLocation
Source ﬁeld 12 import to test::gprogressGlobal
Source ﬁeld 13 import to test::ksection
Source ﬁeld 14 import to test::kgreportNumber
Source ﬁeld 15 import to test::mtestGroup
Source ﬁeld 16 import to test::ktestItemList
Source ﬁeld 17 import to test::rule
Source ﬁeld 18 import to test::kRecordCreatorNode
Source ﬁeld 19 import to test::kRecordModiﬁerNode
Source ﬁeld 20 import to test::RecordModifyDate
Source ﬁeld 21 import to test::testNameRevert ]
[ No dialog ]
#
Go to Layout [ “tableTestLearn” (testlearn) ]
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “testlearn”; Method: Add; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 import to testlearn::_Ltestlearn
Source ﬁeld 2 import to testlearn::ktestSubject
Source ﬁeld 3 import to testlearn::_Number
Source ﬁeld 4 import to testlearn::ktest
Source ﬁeld 5 import to testlearn::Caption
Source ﬁeld 6 import to testlearn::Picture
Source ﬁeld 7 import to testlearn::Location
Source ﬁeld 8 import to testlearn::inUse
Source ﬁeld 9 import to testlearn::kaudienceLocation
Source ﬁeld 10 import to testlearn::InspectionItemCount
Source ﬁeld 11 import to testlearn::CheckboxCaption
Source ﬁeld 12 import to testlearn::recordnumberglobal
Source ﬁeld 13 import to testlearn::recordcountglobal
Source ﬁeld 14 import to testlearn::InspectionItemCountLocation
Source ﬁeld 15 import to testlearn::OK
Source ﬁeld 16 import to testlearn::kcsection
Source ﬁeld 17 import to testlearn::backupPhotoNumber
Source ﬁeld 18 import to testlearn::TimeStart
Source ﬁeld 19 import to testlearn::TimeStop
Source ﬁeld 20 import to testlearn::TimeTotal
Source ﬁeld 21 import to testlearn::kreportNumber
Source ﬁeld 22 import to testlearn::timestamp
Source ﬁeld 24 import to testlearn::orderDiscovery
Source ﬁeld 25 import to testlearn::kcKeywordOther
Source ﬁeld 26 import to testlearn::kNodeOther
Source ﬁeld 27 import to testlearn::kHealth
Source ﬁeld 28 import to testlearn::kNodePrimary
Source ﬁeld 29 import to testlearn::kmedium
Source ﬁeld 30 import to testlearn::kcitation
Source ﬁeld 31 import to testlearn::kﬁleLocation
Source ﬁeld 32 import to testlearn::kfolderPath
Source ﬁeld 33 import to testlearn::kKeywordPrimary
Source ﬁeld 34 import to testlearn::OtherKeyWords
Source ﬁeld 35 import to testlearn::NodeOthers
Source ﬁeld 36 import to testlearn::URL
Source ﬁeld 37 import to testlearn::ﬁlename
Source ﬁeld 38 import to testlearn::kcreference
Source ﬁeld 40 import to testlearn::ﬁlterFind
Source ﬁeld 41 import to testlearn::kRecordCreatorNode
Source ﬁeld 42 import to testlearn::kRecordModiﬁerNode
Source ﬁeld 43 import to testlearn::RecordModifyDate
Source ﬁeld 44 import to testlearn::incomplete
Source ﬁeld 46 import to testlearn::copyrightYear
Source ﬁeld 47 import to testlearn::URLPubDate
Source ﬁeld 48 import to testlearn::kcsample
Source ﬁeld 49 import to testlearn::gkaudienceLocation
Source ﬁeld 50 import to testlearn::kctest
Source ﬁeld 51 import to testlearn::orderTest
Source ﬁeld 52 import to testlearn::title
Source ﬁeld 53 import to testlearn::kctestItem
Source ﬁeld 54 import to testlearn::organEmailRecipient
Source ﬁeld 55 import to testlearn::korgan
Source ﬁeld 56 import to testlearn::kcopyist
Source ﬁeld 57 import to testlearn::emailDate
Source ﬁeld 59 import to testlearn::sampleCasePoint ]
[ No dialog ]
#
Go to Layout [ “tableTag” (tagTable) ]
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “tagTable”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 import to tagTable::kGroupOrTest
Source ﬁeld 2 match with tagTable::_Ltag
Source ﬁeld 3 import to tagTable::tag
Source ﬁeld 4 import to tagTable::orderOrLock
Source ﬁeld 5 import to tagTable::ksection
Source ﬁeld 6 import to tagTable::_Number
Source ﬁeld 7 import to tagTable::match
Source ﬁeld 8 import to tagTable::tagSpelling
Source ﬁeld 9 import to tagTable::kcsection
Source ﬁeld 10 import to tagTable::Kpicture1
Source ﬁeld 11 import to tagTable::notesOrHealth
Source ﬁeld 12 import to tagTable::Ktitle1
Source ﬁeld 13 import to tagTable::kﬁle
Source ﬁeld 15 import to tagTable::Kpicture2
Source ﬁeld 17 import to tagTable::Kpicture3
Source ﬁeld 19 import to tagTable::Ktitle2
Source ﬁeld 20 import to tagTable::Ktitle3
Source ﬁeld 24 import to tagTable::kRecordCreatorNode
Source ﬁeld 25 import to tagTable::kRecordModiﬁerNode ]
[ No dialog ]
#
Go to Layout [ “tableGroupTag” (groupTest) ]
January 7, 平成26 12:03:22 Imagination Quality Management.fp7 - update -1-libraryNewOrUpdate: update
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “groupTest”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 match with groupTest::_Lgroup
Source ﬁeld 2 import to groupTest::_Number
Source ﬁeld 3 import to groupTest::match
Source ﬁeld 4 import to groupTest::name
Source ﬁeld 5 import to groupTest::ksection
Source ﬁeld 6 import to groupTest::defaultSectionInfo
Source ﬁeld 7 import to groupTest::testReportPicture
Source ﬁeld 8 import to groupTest::CaptionORinuseCheck
Source ﬁeld 9 import to groupTest::URLORHealth
Source ﬁeld 10 import to groupTest::order
Source ﬁeld 11 import to groupTest::nameSpelling
Source ﬁeld 12 import to groupTest::kRecordCreatorNode
Source ﬁeld 13 import to groupTest::kSectionCreatorNodesCreator
Source ﬁeld 14 import to groupTest::aboutSection ]
[ No dialog ]
#
Go to Layout [ “tableReference” (reference) ]
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “reference”; Method: Update matching; Add remaining; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 import to reference::_Number
Source ﬁeld 2 match with reference::_Lreference
Source ﬁeld 3 import to reference::ktestSubject
Source ﬁeld 4 import to reference::ktest
Source ﬁeld 5 import to reference::kcsection
Source ﬁeld 6 import to reference::knodePrimary
Source ﬁeld 7 import to reference::pubYear
Source ﬁeld 8 import to reference::URL
Source ﬁeld 9 import to reference::URLdate
Source ﬁeld 10 import to reference::Title
Source ﬁeld 11 import to reference::korgan
Source ﬁeld 12 import to reference::volumeNumber
Source ﬁeld 13 import to reference::PubDate
Source ﬁeld 14 import to reference::pageNumberRange
Source ﬁeld 15 import to reference::kcopyist
Source ﬁeld 16 import to reference::OrginalCitation
Source ﬁeld 17 import to reference::kcopyrightType
Source ﬁeld 18 import to reference::kHealth
Source ﬁeld 19 import to reference::kmedium
Source ﬁeld 20 import to reference::kkeywordOther
Source ﬁeld 21 import to reference::kkeywordPrimary
Source ﬁeld 22 import to reference::thoughtsNotesEtc
Source ﬁeld 23 import to reference::kfolderpath
Source ﬁeld 24 import to reference::ﬁleName
Source ﬁeld 27 import to reference::referenceNodes
Source ﬁeld 28 import to reference::CopyrightYear
Source ﬁeld 29 import to reference::kcopyrightHolder
Source ﬁeld 30 import to reference::referenceDump
Source ﬁeld 31 import to reference::knodeOther
Source ﬁeld 32 import to reference::NodeOthers
Source ﬁeld 33 import to reference::OtherKeyWords
Source ﬁeld 34 import to reference::referenceNodesOLD
Source ﬁeld 35 import to reference::ﬁlterFind
Source ﬁeld 36 import to reference::picture
Source ﬁeld 37 import to reference::kﬁleLocation
Source ﬁeld 38 import to reference::rights
Source ﬁeld 39 import to reference::mFileLocation
Source ﬁeld 40 import to reference::kcitation
Source ﬁeld 41 import to reference::incomplete
Source ﬁeld 42 import to reference::lock
Source ﬁeld 44 import to reference::kcreatorNode
Source ﬁeld 45 import to reference::kmodiﬁerNode
Source ﬁeld 46 import to reference::modifyDate
Source ﬁeld 48 import to reference::TimeRange
Source ﬁeld 51 import to reference::createDate
Source ﬁeld 52 import to reference::show
Source ﬁeld 53 import to reference::library only
Source ﬁeld 54 import to reference::URLdoi
Source ﬁeld 55 import to reference::issueNumber
Source ﬁeld 56 import to reference::publisherLocation
Source ﬁeld 57 import to reference::compilationTitle
Source ﬁeld 58 import to reference::compilationEditors
Source ﬁeld 59 import to reference::kmedia
Source ﬁeld 60 import to reference::kmediaType
Source ﬁeld 61 import to reference::compilationNumberOfEditors
Source ﬁeld 62 import to reference::pubYearMonthRange
Source ﬁeld 63 import to reference::ISBN
Source ﬁeld 64 import to reference::pubDateOther
Source ﬁeld 65 import to reference::bookChapter
Source ﬁeld 66 import to reference::letterDate
Source ﬁeld 67 import to reference::compilationAbbr
Source ﬁeld 68 import to reference::emailRecipient
Source ﬁeld 69 import to reference::conferenceIntroWords
Source ﬁeld 70 import to reference::conferenceTitle
Source ﬁeld 71 import to reference::conferenceSubTitle
Source ﬁeld 72 import to reference::conferenceLocation
Source ﬁeld 73 import to reference::conferenceDate
Source ﬁeld 74 import to reference::conferenceGroupName
Source ﬁeld 75 import to reference::TypeOfMediumOther
Source ﬁeld 76 import to reference::GovernmentDocInfo
Source ﬁeld 77 import to reference::governmentAuthor
Source ﬁeld 78 import to reference::ISSN
Source ﬁeld 79 import to reference::publisherTypeAlternative
Source ﬁeld 80 import to reference::copyrightOtherHolder
Source ﬁeld 81 import to reference::publisherTypeOther
Source ﬁeld 82 import to reference::pageNumberOther
Source ﬁeld 83 import to reference::dissertationThesisUniversity ]
[ No dialog ]
#
Go to Layout [ “tableReport” (report) ]
Show All Records
Import Records [ Source: “$ﬁlepath”; Target: “report”; Method: Add; Character Set: “Unicode”; Field Mapping: Source ﬁeld 1 import to report::_Lreport
Source ﬁeld 2 import to report::_Number
Source ﬁeld 3 import to report::ktestSubject
Source ﬁeld 4 import to report::_kfContactGeography
Source ﬁeld 5 import to report::general_info
Source ﬁeld 6 import to report::ktest
Source ﬁeld 7 import to report::krecommendation
Source ﬁeld 8 import to report::order
Source ﬁeld 9 import to report::Picture
Source ﬁeld 10 import to report::kthingRecommendationID
Source ﬁeld 11 import to report::kgeneralSpeciﬁcItemRecommendationID
Source ﬁeld 12 import to report::_kfPhoto
Source ﬁeld 13 import to report::_kfContactGeography2
Source ﬁeld 14 import to report::_kfContactGeography3
Source ﬁeld 15 import to report::_kfContactGeography4
Source ﬁeld 16 import to report::_kfContactGeography5
Source ﬁeld 17 import to report::PictureCaption
Source ﬁeld 18 import to report::textMain
Source ﬁeld 19 import to report::textPhotoRow1
Source ﬁeld 20 import to report::pagenumberItem
Source ﬁeld 21 import to report::CurrentRecord
Source ﬁeld 22 import to report::_kfPhoto2
Source ﬁeld 23 import to report::_kfPhoto3
Source ﬁeld 24 import to report::_kfPhoto4
Source ﬁeld 25 import to report::pagenumberTheme
Source ﬁeld 26 import to report::TOC
Source ﬁeld 27 import to report::TOCnumbers
Source ﬁeld 28 import to report::ReportCover
Source ﬁeld 29 import to report::ReportPDFtitle
Source ﬁeld 30 import to report::kreportNumber
Source ﬁeld 31 import to report::ksection
Source ﬁeld 32 import to report::kRecordCreatorNode
Source ﬁeld 33 import to report::kRecordModiﬁerNode
Source ﬁeld 34 import to report::RecordModifyDate
Source ﬁeld 35 import to report::khealth
Source ﬁeld 36 import to report::textPhotoRow2 ]
[ No dialog ]
#
Set Field [ backup::backup; "" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Layout [ “defaultNode1” (tagMenus) ]
// Perform Script [ “defaultNodeMenu” ]
Select Window [ Name: "Setup"; Current ﬁle ]
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Set Field [ backup::backup; "" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
#
Set Variable [ $$import; Value:1 ]
#
January 7, 平成26 12:03:22 Imagination Quality Management.fp7 - update -2-
