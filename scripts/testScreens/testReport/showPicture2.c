testScreens: testReport: showPicture2
#
#Show picture in picture window.
Set Variable [ $$PictureOnReportLayout; Value:testlearn2::_Ltestlearn ]
If [ $$PictureOnReportLayout ≠ "" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
End If
January 5, ଘ౮28 16:10:44 Library.fp7 - showPicture2 -1-
