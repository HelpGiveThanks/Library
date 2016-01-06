testScreens: testReport: showPicture1
#
#Show picture in picture window.
Set Variable [ $$PictureOnReportLayout; Value:testlearnReportTags::_Ltestlearn ]
If [ $$PictureOnReportLayout ≠ "" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
End If
January 5, ଘ౮28 16:11:33 Library.fp7 - showPicture1 -1-
