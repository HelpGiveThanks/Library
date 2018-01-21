January 19, 2018 14:31:03 Library.fmp12 - loadReportTestResultRecord -1-
tagMenu: loadReportTestResultRecord
#
#Stop loading record if other script is running.
If [ $$stopLoadTestResultRecord = 1 ]
Exit Script [ ]
End If
#
#Conditionally format record if used in
#main Report window.
#
#This key effects the conditional formatting
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $$main; Value:testlearnReportTags::_Ltestlearn ]
Go to Field [ ]
#
#Refresh conditional formatting in both
#windows and return to Tag Menus window.
Select Window [ Name: "Report"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#
#Close any open test item reference windows.
#NOTE: This is next loop is a work around to
#deal with the Reference window issue.
#Basically, there are several scripts that may
#open Reference windows for Info records that
#have references. Rather than try to figure out all
#the ways this occurs (easy with time), this loop
#just closes as many Reference windows as are
#currently open. Not the best solution, but it
#works and I really want to close out work on this
#4.0beta version and move on.
Loop
If [ ValueCount ( FilterValues ( WindowNames ( Get ( FileName ) ) ; "Reference" ) ) > 0 ]
Close Window [ Name: "Reference"; Current file ]
Set Variable [ $resizeTagMenusWindow; Value:1 ]
End If
Exit Loop If [ ValueCount ( FilterValues ( WindowNames ( Get ( FileName ) ) ; "Reference" ) ) = 0 ]
End Loop
#
#
#Resize the Tag Menus window. Resize the Test
#window if currently in the Test Section.
If [ $resizeTagMenusWindow ≠ "" ]
If [ $$pictureWindowColor = "test" ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2 ]
#
#The size of the Tag Menus window in the Report
#section can be larger than half the window width.
Else
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get (ScreenWidth) - 594; Left: 594 ]
End If
#
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#
