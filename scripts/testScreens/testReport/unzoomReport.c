testScreens: testReport: UnzoomReport
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$ﬁrst ]
Set Variable [ $$last; Value:report::ktest ]
Set Field [ TEMP::kuserLocation; "" ]
#[by David Matson 4.16.11, last modiﬁed by same 4.18.11]
#clear the $$ﬁnding and $window variables
Set Variable [ $$ﬁnding ]
Set Variable [ $$window ]
Set Variable [ $contact; Value:report::ktestSubject ]
Set Variable [ $item; Value:report::ktest ]
#basic administration tasks
Select Window [ Name: "Tag Menus"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menu"; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0; Left: Get ( ScreenWidth ) / 2 ]
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; $contact ]
Set Field [ testlearnReportTags::ktest; $item ]
Set Field [ testlearnReportTags::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: testlearnReportTags::Location; ascending
testlearnReportTags::timestamp; ascending
testlearnReportTags::_Ltestlearn; ascending ]
[ Restore; No dialog ]
End If
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0; Left: Get ( ScreenWidth ) / 2 ]
Set Zoom Level
[ 100% ]
// If [ Get (WindowZoomLevel) = 100 ]
// Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 480; Top: 0; Left: 0 ]
// Set Zoom Level
[ 150% ]
// Else If [ Get (WindowZoomLevel) = 150 ]
// Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 634; Top: 0; Left: 0 ]
// Set Zoom Level
[ 200% ]
// Else If [ Get (WindowZoomLevel) = 200 ]
// Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 942; Top: 0; Left: 0 ]
// Set Zoom Level
[ 300% ]
// End If
Select Window [ Name: "Report"; Current ﬁle ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: Get ( ScreenWidth ) / 2; Top: 0; Left: 0 ]
Set Zoom Level
[ 100% ]
January 7, 平成26 14:27:25 Imagination Quality Management.fp7 - UnzoomReport -1-
