testScreens: testReport: reportClearDiscoveryLink
#If user is trying to clear a blank field
#stop the script
If [ Get (ActiveFieldContents) = "" ]
Go to Field [ ]
Halt Script
End If
#
#
#Get ID then clear field.
Set Variable [ $clear; Value:Get ( ActiveFieldContents ) ]
Clear [ ]
[ Select ]
Go to Field [ ]
#
#tell user it is not in use
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LayoutName) ≠ "reportTagDiscovery" ]
Perform Script [ “reportTagDiscovery” ]
End If
Go to Field [ ]
#
#find the record that has been copied and cleared
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $clear = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If it is not a discovery record, go to the info layout.
If [ $clear ≠ testlearnReportTags::_Ltestlearn ]
Perform Script [ “reportTagInfo” ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Loop
Exit Loop If [ $clear = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadtestinfo” ]
End If
#
#inform the user that it is not being used in the Report window
#by removing it from the list of inUse report sections,
#basically removing it from showing on this page but
#not the other pages it is currently being used by.
Set Variable [ $inUse; Value:testlearnReportTags::inUse ]
Set Field [ testlearnReportTags::inUse; Substitute ( testlearnReportTags::inUse ; $$contact & $$reportNumber & "¶" ; "" ) ]
Refresh Window
#
Select Window [ Name: "Report"; Current file ]
January 7, 平成26 14:44:06 Imagination Quality Management.fp7 - reportClearDiscoveryLink -1-
