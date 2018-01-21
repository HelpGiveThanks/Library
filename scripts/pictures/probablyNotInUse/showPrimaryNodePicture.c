January 19, 2018 2:51:41 Library.fmp12 - showPrimaryNodePicture -1-
pictures: probablyNotInUse: showPrimaryNodePicture
#
#
Set Variable [ $$defaultPrimaryNodePicture; Value:PictureDefaultNode::_Lreference ]
Set Variable [ $$fileLocation; Value:Case (
PictureDefaultNode::picture ≠ "" ; "database" ;
PictureDefaultNode::kfileLocation ≠ "" and PictureDefaultNode::fileName ≠ "" and PictureDefaultNode::showMedia = "" ;
"harddrive" ;
PictureDefaultNode::URL ≠ "" and PictureDefaultNode::showMedia ≠ "" ; "web" ;
"none" ) ]
#
#
If [ $$fileLocation ≠ "none" ]
Perform Script [ “showCitationPicture1inNewWindow” ]
End If
