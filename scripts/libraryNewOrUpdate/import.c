libraryNewOrUpdate: import
#create unique ID for closing import file
Go to Layout [ “tempStart” (TEMP) ]
New Record/Request
Set Field [ TEMP::import; "adﬂki3ina;lkfjie8;la;lkdvnma;ldieiasoerueoilanldf83984798374iwuhelfkjdlsidufioawkel" ]
Copy [ TEMP::import ]
[ Select ]
Set Field [ TEMP::import; "" ]
#open import file. Its startup script will ID it for close
#and will copy its filepath for use in this script
Set Error Capture [ On ]
Allow User Abort [ Off ]
Open File [ <unknown> ]
[ Open hidden ]
If [ Get (LastError) = 1 ]
Delete Record/Request
[ No dialog ]
Go to Layout [ original layout ]
Exit Script [ ]
End If
// Close Window [ Name: "import" ]
#set file path for import
Paste [ TEMP::filePath ]
[ Select; No style ]
Set Variable [ $path; Value:TEMP::filePath ]
Delete Record/Request
[ No dialog ]
Go to Layout [ original layout ]
#
#import node
Show All Records
Import Records [ Source: “$path”; Method: Add; Character Set: “Mac Roman” ]
[ No dialog ]
#
#import item
Go to Layout [ “tableTest” (test) ]
Show All Records
Import Records [ Source: “$path”; Target: “test”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source field 1 import to test::_Ltest
Source field 2 import to test::ktestGroup
Source field 3 import to test::_number
Source field 4 import to test::kcfocusALL
Source field 5 import to test::testName
Source field 6 import to test::order
Source field 7 import to test::retire
Source field 9 import to test::kgtester
Source field 12 import to test::glocationNameGlobal
Source field 13 import to test::gcontactNameGlobal
Source field 14 import to test::kgaudienceLocation
Source field 15 import to test::gprogressGlobal
Source field 16 import to test::ksection
Source field 17 import to test::kgreportNumber
Source field 21 import to test::mtestGroup
Source field 22 import to test::ktestItemList
Source field 23 import to test::rule
Source field 24 import to test::kRecordCreatorNode
Source field 25 import to test::kRecordModifierNode
Source field 26 import to test::RecordModifyDate
Source field 27 import to test::testNameRevert ]
[ No dialog ]
#
#import evidence
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Show All Records
Import Records [ Source: “$path”; Target: “testlearnReportTags”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source field 1 import to testlearnReportTags::_Ltestlearn
Source field 2 import to testlearnReportTags::ktestSubject
Source field 3 import to testlearnReportTags::_Number
Source field 5 import to testlearnReportTags::ktest
Source field 6 import to testlearnReportTags::Caption
Source field 7 import to testlearnReportTags::Picture
Source field 8 import to testlearnReportTags::Location
Source field 9 import to testlearnReportTags::inUse
Source field 10 import to testlearnReportTags::kaudienceLocation
Source field 11 import to testlearnReportTags::InspectionItemCount
Source field 12 import to testlearnReportTags::CheckboxCaption
Source field 13 import to testlearnReportTags::recordnumberglobal
Source field 14 import to testlearnReportTags::recordcountglobal
Source field 15 import to testlearnReportTags::InspectionItemCountLocation
Source field 16 import to testlearnReportTags::OK
Source field 17 import to testlearnReportTags::kcsection
Source field 18 import to testlearnReportTags::backupPhotoNumber
Source field 19 import to testlearnReportTags::TimeStart
Source field 20 import to testlearnReportTags::TimeStop
Source field 21 import to testlearnReportTags::TimeTotal
Source field 23 import to testlearnReportTags::kreportNumber
Source field 24 import to testlearnReportTags::timestamp
Source field 26 import to testlearnReportTags::orderDiscovery
Source field 27 import to testlearnReportTags::kcKeywordOther
Source field 28 import to testlearnReportTags::kNodeOther
Source field 29 import to testlearnReportTags::kHealth
Source field 30 import to testlearnReportTags::kNodePrimary
Source field 31 import to testlearnReportTags::kmedium
Source field 32 import to testlearnReportTags::kcitation
Source field 33 import to testlearnReportTags::kfileLocation
Source field 34 import to testlearnReportTags::kfolderPath
Source field 35 import to testlearnReportTags::kKeywordPrimary
Source field 36 import to testlearnReportTags::OtherKeyWords
Source field 37 import to testlearnReportTags::NodeOthers
Source field 38 import to testlearnReportTags::URL
Source field 39 import to testlearnReportTags::filename
Source field 40 import to testlearnReportTags::kcreference
Source field 42 import to testlearnReportTags::filterFind
Source field 43 import to testlearnReportTags::kRecordCreatorNode
Source field 44 import to testlearnReportTags::kRecordModifierNode
Source field 45 import to testlearnReportTags::RecordModifyDate
Source field 46 import to testlearnReportTags::incomplete
Source field 48 import to testlearnReportTags::copyrightYear
Source field 49 import to testlearnReportTags::URLPubDate
Source field 50 import to testlearnReportTags::kcsample
Source field 51 import to testlearnReportTags::gkaudienceLocation
Source field 52 import to testlearnReportTags::kctest
Source field 53 import to testlearnReportTags::orderTest
Source field 54 import to testlearnReportTags::title
Source field 55 import to testlearnReportTags::kctestItem
Source field 56 import to testlearnReportTags::organEmailRecipient
Source field 57 import to testlearnReportTags::korgan
Source field 58 import to testlearnReportTags::kcopyist
Source field 59 import to testlearnReportTags::emailDate
Source field 61 import to testlearnReportTags::sampleCasePoint ]
[ No dialog ]
#
#import locationdetail
Go to Layout [ “tableTag” (tagTable) ]
Show All Records
Import Records [ Source: “$path”; Target: “tagTable”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source field 1 import to tagTable::kGroupOrTest
Source field 2 import to tagTable::_Ltag
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
#import text
Go to Layout [ <unknown> ]
Show All Records
Import Records [ Source: “$path”; Method: Add; Character Set: “Mac Roman” ]
[ No dialog ]
#
January 7, 平成26 12:07:40 Imagination Quality Management.fp7 - import -1-libraryNewOrUpdate: import
#
#import nodeLocation
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Show All Records
Import Records [ Source: “$path”; Target: “tagTestSubjectLocation”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source field 1 import to tagTestSubjectLocation::knode
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
#import sectionkind
Go to Layout [ “tableGroupTag” (groupTest) ]
Show All Records
Import Records [ Source: “$path”; Target: “groupTest”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source field 1 import to groupTest::_Lgroup
Source field 2 import to groupTest::_Number
Source field 4 import to groupTest::match
Source field 5 import to groupTest::name
Source field 6 import to groupTest::ksection
Source field 7 import to groupTest::defaultSectionInfo
Source field 8 import to groupTest::testReportPicture
Source field 9 import to groupTest::CaptionORinuseCheck
Source field 10 import to groupTest::URLORHealth
Source field 11 import to groupTest::order
Source field 12 import to groupTest::nameSpelling
Source field 13 import to groupTest::kRecordCreatorNode
Source field 14 import to groupTest::kSectionCreatorNodesCreator
Source field 15 import to groupTest::aboutSection ]
[ No dialog ]
#
#import report
Go to Layout [ “PrintReportEdit” (report) ]
Show All Records
Import Records [ Source: “$path”; Target: “report”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source field 1 import to report::_Lreport
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
#go to main screen
Go to Layout [ <unknown> ]
January 7, 平成26 12:07:40 Imagination Quality Management.fp7 - import -2-
