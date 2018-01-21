January 15, 2018 18:02:25 Library.fmp12 - showTestSubjectCopyrightPicture -1-
pictures: showTestSubjectCopyrightPicture
#
#
Set Variable [ $$defaultTestSubjecPicture; Value:testSubjectsCopyrightPicture::_Lreference ]
Set Variable [ $$fileLocation; Value:Case (
testSubjectsCopyrightPicture::picture ≠ "" ; "database" ;
testSubjectsCopyrightPicture::kfileLocation ≠ "" and testSubjectsCopyrightPicture::fileName ≠ "" and testSubjectsCopyrightPicture::
showMedia = "" ; "harddrive" ;
testSubjectsCopyrightPicture::URL ≠ "" and testSubjectsCopyrightPicture::showMedia ≠ "" ; "web" ;
"none" ) ]
#
#
If [ $$fileLocation ≠ "none" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
End If
