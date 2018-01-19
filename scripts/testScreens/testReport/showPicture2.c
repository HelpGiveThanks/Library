January 15, 2018 15:32:21 Library.fmp12 - showPicture2 -1-
test: report: showPicture2
#
#Show picture in picture window...
Set Variable [ $$PictureOnReportLayout; Value:testlearnReportTags 2::_Ltestlearn ]
Set Variable [ $$fileLocation; Value:Case ( testlearnReportTags 2::picture ≠ "" ; "TLpicture" ;
Case (
refShowMediaReport 2::picture ≠ "" ; "database" ;
refShowMediaReport 2::kfileLocation ≠ "" and refShowMediaReport 2::fileName ≠ "" and refShowMediaReport 2::showMedia = "" ;
"harddrive" ;
refShowMediaReport 2::URL ≠ "" and refShowMediaReport 2::showMedia ≠ "" ; "web" ;
"none" )
) ]
#
#... if there is a picture to show.
If [ $$PictureOnReportLayout ≠ "" and $$fileLocation ≠ "none" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
#
#Otherwise, do nothing.
Else
Set Variable [ $$PictureOnReportLayout ]
Set Variable [ $$fileLocation ]
#
#Inform user about how to add media.
Show Custom Dialog [ Message: "To add a picture or movie to this slot 1) select a test result in the Tag Menus window that has
media. 2) Click this result's copy button. 3) Return to this Report window. 4) Click in the highlighted space below."; Default
Button: “OK”, Commit: “No” ]
End If
