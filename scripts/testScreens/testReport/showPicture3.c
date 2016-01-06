testScreens: testReport: showPicture3
#
#Show picture in picture window.
Set Variable [ $$PictureOnReportLayout; Value:testlearn3::_Ltestlearn ]
If [ $$PictureOnReportLayout ≠ "" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
End If
January 5, ଘ౮28 16:08:36 Library.fp7 - showPicture3 -1-
