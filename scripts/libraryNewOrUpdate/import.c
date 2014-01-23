libraryNewOrUpdate: import
#create unique ID for closing import ﬁle
Go to Layout [ “tempStart” (TEMP) ]
New Record/Request
Set Field [ TEMP::import; "adﬂki3ina;lkfjie8;la;lkdvnma;ldieiasoerueoilanldf83984798374iwuhelfkjdlsiduﬁoawkel" ]
Copy [ TEMP::import ]
[ Select ]
Set Field [ TEMP::import; "" ]
#open import ﬁle. Its startup script will ID it for close
#and will copy its ﬁlepath for use in this script
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
#set ﬁle path for import
Paste [ TEMP::ﬁlePath ]
[ Select; No style ]
Set Variable [ $path; Value:TEMP::ﬁlePath ]
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
Import Records [ Source: “$path”; Target: “test”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source ﬁeld 1 import to test::_Ltest
Source ﬁeld 2 import to test::ktestGroup
Source ﬁeld 3 import to test::_number
Source ﬁeld 4 import to test::kcfocusALL
Source ﬁeld 5 import to test::testName
Source ﬁeld 6 import to test::order
Source ﬁeld 7 import to test::retire
Source ﬁeld 9 import to test::kgtester
Source ﬁeld 12 import to test::glocationNameGlobal
Source ﬁeld 13 import to test::gcontactNameGlobal
Source ﬁeld 14 import to test::kgaudienceLocation
Source ﬁeld 15 import to test::gprogressGlobal
Source ﬁeld 16 import to test::ksection
Source ﬁeld 17 import to test::kgreportNumber
Source ﬁeld 21 import to test::mtestGroup
Source ﬁeld 22 import to test::ktestItemList
Source ﬁeld 23 import to test::rule
Source ﬁeld 24 import to test::kRecordCreatorNode
Source ﬁeld 25 import to test::kRecordModiﬁerNode
Source ﬁeld 26 import to test::RecordModifyDate
Source ﬁeld 27 import to test::testNameRevert ]
[ No dialog ]
#
#import evidence
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Show All Records
Import Records [ Source: “$path”; Target: “testlearnReportTags”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source ﬁeld 1 import to testlearnReportTags::_Ltestlearn
Source ﬁeld 2 import to testlearnReportTags::ktestSubject
Source ﬁeld 3 import to testlearnReportTags::_Number
Source ﬁeld 5 import to testlearnReportTags::ktest
Source ﬁeld 6 import to testlearnReportTags::Caption
Source ﬁeld 7 import to testlearnReportTags::Picture
Source ﬁeld 8 import to testlearnReportTags::Location
Source ﬁeld 9 import to testlearnReportTags::inUse
Source ﬁeld 10 import to testlearnReportTags::kaudienceLocation
Source ﬁeld 11 import to testlearnReportTags::InspectionItemCount
Source ﬁeld 12 import to testlearnReportTags::CheckboxCaption
Source ﬁeld 13 import to testlearnReportTags::recordnumberglobal
Source ﬁeld 14 import to testlearnReportTags::recordcountglobal
Source ﬁeld 15 import to testlearnReportTags::InspectionItemCountLocation
Source ﬁeld 16 import to testlearnReportTags::OK
Source ﬁeld 17 import to testlearnReportTags::kcsection
Source ﬁeld 18 import to testlearnReportTags::backupPhotoNumber
Source ﬁeld 19 import to testlearnReportTags::TimeStart
Source ﬁeld 20 import to testlearnReportTags::TimeStop
Source ﬁeld 21 import to testlearnReportTags::TimeTotal
Source ﬁeld 23 import to testlearnReportTags::kreportNumber
Source ﬁeld 24 import to testlearnReportTags::timestamp
Source ﬁeld 26 import to testlearnReportTags::orderDiscovery
Source ﬁeld 27 import to testlearnReportTags::kcKeywordOther
Source ﬁeld 28 import to testlearnReportTags::kNodeOther
Source ﬁeld 29 import to testlearnReportTags::kHealth
Source ﬁeld 30 import to testlearnReportTags::kNodePrimary
Source ﬁeld 31 import to testlearnReportTags::kmedium
Source ﬁeld 32 import to testlearnReportTags::kcitation
Source ﬁeld 33 import to testlearnReportTags::kﬁleLocation
Source ﬁeld 34 import to testlearnReportTags::kfolderPath
Source ﬁeld 35 import to testlearnReportTags::kKeywordPrimary
Source ﬁeld 36 import to testlearnReportTags::OtherKeyWords
Source ﬁeld 37 import to testlearnReportTags::NodeOthers
Source ﬁeld 38 import to testlearnReportTags::URL
Source ﬁeld 39 import to testlearnReportTags::ﬁlename
Source ﬁeld 40 import to testlearnReportTags::kcreference
Source ﬁeld 42 import to testlearnReportTags::ﬁlterFind
Source ﬁeld 43 import to testlearnReportTags::kRecordCreatorNode
Source ﬁeld 44 import to testlearnReportTags::kRecordModiﬁerNode
Source ﬁeld 45 import to testlearnReportTags::RecordModifyDate
Source ﬁeld 46 import to testlearnReportTags::incomplete
Source ﬁeld 48 import to testlearnReportTags::copyrightYear
Source ﬁeld 49 import to testlearnReportTags::URLPubDate
Source ﬁeld 50 import to testlearnReportTags::kcsample
Source ﬁeld 51 import to testlearnReportTags::gkaudienceLocation
Source ﬁeld 52 import to testlearnReportTags::kctest
Source ﬁeld 53 import to testlearnReportTags::orderTest
Source ﬁeld 54 import to testlearnReportTags::title
Source ﬁeld 55 import to testlearnReportTags::kctestItem
Source ﬁeld 56 import to testlearnReportTags::organEmailRecipient
Source ﬁeld 57 import to testlearnReportTags::korgan
Source ﬁeld 58 import to testlearnReportTags::kcopyist
Source ﬁeld 59 import to testlearnReportTags::emailDate
Source ﬁeld 61 import to testlearnReportTags::sampleCasePoint ]
[ No dialog ]
#
#import locationdetail
Go to Layout [ “tableTag” (tagTable) ]
Show All Records
Import Records [ Source: “$path”; Target: “tagTable”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source ﬁeld 1 import to tagTable::kGroupOrTest
Source ﬁeld 2 import to tagTable::_Ltag
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
Import Records [ Source: “$path”; Target: “tagTestSubjectLocation”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source ﬁeld 1 import to tagTestSubjectLocation::knode
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
#import sectionkind
Go to Layout [ “tableGroupTag” (groupTest) ]
Show All Records
Import Records [ Source: “$path”; Target: “groupTest”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source ﬁeld 1 import to groupTest::_Lgroup
Source ﬁeld 2 import to groupTest::_Number
Source ﬁeld 4 import to groupTest::match
Source ﬁeld 5 import to groupTest::name
Source ﬁeld 6 import to groupTest::ksection
Source ﬁeld 7 import to groupTest::defaultSectionInfo
Source ﬁeld 8 import to groupTest::testReportPicture
Source ﬁeld 9 import to groupTest::CaptionORinuseCheck
Source ﬁeld 10 import to groupTest::URLORHealth
Source ﬁeld 11 import to groupTest::order
Source ﬁeld 12 import to groupTest::nameSpelling
Source ﬁeld 13 import to groupTest::kRecordCreatorNode
Source ﬁeld 14 import to groupTest::kSectionCreatorNodesCreator
Source ﬁeld 15 import to groupTest::aboutSection ]
[ No dialog ]
#
#import report
Go to Layout [ “PrintReportEdit” (report) ]
Show All Records
Import Records [ Source: “$path”; Target: “report”; Method: Add; Character Set: “Mac Roman”; Field Mapping: Source ﬁeld 1 import to report::_Lreport
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
#go to main screen
Go to Layout [ <unknown> ]
January 7, 平成26 12:07:40 Imagination Quality Management.fp7 - import -2-
