January 15, 2018 15:31:27 Library.fmp12 - showPicture1 -1-
test: report: showPicture1
#
#Show picture in picture window...
Set Variable [ $$PictureOnReportLayout; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $$fileLocation; Value:Case ( testlearnReportTags::picture ≠ "" ; "TLpicture" ;
Case (
refTestShowMedia::picture ≠ "" ; "database" ;
refTestShowMedia::kfileLocation ≠ "" and refTestShowMedia::fileName ≠ "" and refTestShowMedia::showMedia = "" ; "harddrive" ;
refTestShowMedia::URL ≠ "" and refTestShowMedia::showMedia ≠ "" ; "web" ;
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
Button: “OK”, Commit: “Yes” ]
End If
