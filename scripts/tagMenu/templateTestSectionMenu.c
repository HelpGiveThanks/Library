January 15, 2018 16:53:57 Library.fmp12 - templateTestSectionMenu -1-
tagMenu: templateTestSectionMenu
#
#
#Don't go to the test module if the user has
#not selected a primary node, or a copyright.
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating new records) by clicking the node button.";
Default Button: “OK”, Commit: “Yes” ]
Halt Script
Else If [ tempSetup::kdefaultCopyright = "" ]
Show Custom Dialog [ Message: "Select the default copyright for any new records that you create by clicking the copyright button
(you can always change your mind)."; Default Button: “OK”, Commit: “No” ]
Halt Script
End If
#
#Sections shown are the template sections
#for a test. This tag window will be used to create
#specific sections from a template for test subjects.
#So in the Setup window the system highlights
#the test subject for whom the sections are going
#to be created, and who are going to be tested.
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$citationitem ]
Set Variable [ $$testSubject; Value:tempSetup::kdefaultNodeTestSubject ]
Set Field [ TEMP::DEFAULTNodeTestSubjectName; testSubject::tag ]
Refresh Window
#
#Find all created test section records.
Go to Layout [ “defaultTest” (testSectionCreatedFromATemplate) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Show All Records
#
#Sort
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubjectName::tag; ascending
testSectionCreatedFromATemplate::reportNumber; descending
testSectionCreatedFromATemplate::order; based on value list: “order Pulldown List”
testSectionCreatedFromATemplate::name; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
#
