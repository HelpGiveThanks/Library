pictures: selectRefMediaForLearnRecord
#
#This script is activited by the picture
#selection button on the QV layout. It allows
#the user to show a selected reference's
#media in the layout's picture window.
If [ testlearn::Picture = "" ]
If [ testlearn::kshowReferencedMedia = refReference::_Lreference ]
Set Field [ testlearn::kshowReferencedMedia; "" ]
Else If [ //There is a picture to show if...
refReference::picture ≠ "" or
refReference::showMedia ≠ "" and refReference::URL ≠ "" or
refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "jpg"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "gif"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "eps"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "jp2"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "psd"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "png"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "pct"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "pcs"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = ".qt"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "sgi"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "tga"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "tif"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "bmp"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "wmf"
or refReference::kfileLocation ≠ "" and refReference::fileName ≠ "" and Right ( refReference::fileName ; 3 ) = "emf" or
refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "jpg"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "gif"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "eps"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "jp2"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "psd"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "png"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "pct"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "pcs"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= ".qt"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "sgi"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "tga"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "tif"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "bmp"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "wmf"
or refReference::URL ≠ "" and Right ( refReference::URL ; 3 )= "emf" ]
Set Field [ testlearn::kshowReferencedMedia; refReference::_Lreference ]
Else
Show Custom Dialog [ Message: "This reference has no media to show. Picture button will be a darker grey if there is
media to show."; Buttons: “OK” ]
End If
#
Else
#If the learn record has a picture then stop
#this script and tell the user to remove it
#before adding a reference picture.
Set Field [ testlearn::kshowReferencedMedia; "" ]
Show Custom Dialog [ Message: "This record has a picture which must be removed before selecting to show a reference's
picture. To remove it, 1) Click on the picture. 2) Click the 'x' button in the picture window."; Buttons: “OK” ]
End If
January 6, ଘ౮28 14:49:46 Library.fp7 - selectRefMediaForLearnRecord -1-
