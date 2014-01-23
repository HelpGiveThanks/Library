testScreens: testReport: CHUNK_gotoItemViaPulldown
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Field [ TEMP::kuserLocation; "" ]
#[by David Matson 4.16.11, last modiﬁed by same 4.18.11]
#clear the $$ﬁnding and $window variables
Set Variable [ $$ﬁnding ]
Set Variable [ $$window ]
Set Variable [ $contact; Value:report::ktestSubject ]
Set Variable [ $item; Value:TEMP::ktest ]
#
#clear global ﬁelds for creating new discovery
#records, but put in current timestamp to help
#user understand how info sould be put into
#the timestample ﬁeld and for easy editing,
#changing date, time, etc.
Set Field [ testlearnReportTags::gkaudienceLocation; "" ]
Set Field [ TEMP::LocationName; "" ]
Set Field [ TEMP::TimeStamp; Get ( CurrentTimeStamp ) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $contact ]
Set Field [ report::ktest; $item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: report::ktest; ascending ]
[ Restore; No dialog ]
#
#****haven't decided to use globals or $$variables. Since $$item is used in many other scripts I'm capturing it here.
Set Field [ TEMP::ktest; report::ktest ]
Set Field [ TEMP::ktestItemList; report::ktest ]
Set Variable [ $$item; Value:report::ktest ]
Set Field [ TEMP::testName; reportItem::testName ]
Set Field [ TEMP::showFavorites; "" ]
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get ( ScreenHeight ); Width: 330; Left: 0 ]
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
End If
If [ Left ( Get (LayoutName) ; 18 ) = "reportTagDiscovery" ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktest; TEMP::ktest ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: testlearnReportTags::Location; ascending
testlearnReportTags::timestamp; ascending
testlearnReportTags::_Ltestlearn; ascending ]
[ Restore; No dialog ]
Else If [ Left ( Get (LayoutName) ; 13 ) = "reportTagInfo" ]
Perform Script [ “reportTagInfo” ]
Else
#
#Find test list key as it may be different from test key.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “testSetup” (test) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ test::_Ltest; TEMP::ktest ]
Perform Find [ ]
Set Field [ TEMP::ktestItemList; test::ktestItemList ]
Go to Layout [ “reportTagItem” (tagMenus) ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID ]
#
#Find test items for section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ ruleTagMenuTestGroups::match; TEMP::ktestItemList & ¶ ]
Perform Find [ ]
#
Sort Records [ Speciﬁed Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::name; ascending
ruleTagMenuTestGroups::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
#
End If
Select Window [ Name: "Report"; Current ﬁle ]
#[validated by David Matson 4.18.11]
#
January 7, 平成26 14:25:54 Imagination Quality Management.fp7 - CHUNK_gotoItemViaPulldown -1-
