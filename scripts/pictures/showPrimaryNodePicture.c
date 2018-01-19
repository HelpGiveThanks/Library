pictures: showPrimaryNodePicture
#
#
Set Variable [ $$defaultPrimaryNodePicture; Value:defaultPictureRef::_Lreference ]
Set Variable [ $$fileLocation; Value:Case (
defaultPictureRef::picture ≠ "" ; "database" ;
defaultPictureRef::kfileLocation ≠ "" and defaultPictureRef::fileName ≠ "" and defaultPictureRef::showMedia = "" ; "harddrive" ;
defaultPictureRef::URL ≠ "" and defaultPictureRef::showMedia ≠ "" ; "web" ;
"none" ) ]
#
#
If [ $$fileLocation ≠ "none" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
End If
August 20, ଘ౮28 14:41:44 Library.fp7 - showPrimaryNodePicture -1-
