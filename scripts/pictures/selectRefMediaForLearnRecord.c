pictures: selectRefMediaForLearnRecord
#
#This script is activited by the picture
#selection button on the QV layout. It allows
#the user to show a the selected reference's
#media in the layouts picture window.
If [ testlearn::kshowReferencedMedia = refReference::_Lreference ]
Set Field [ testlearn::kshowReferencedMedia; "" ]
Else
Set Field [ testlearn::kshowReferencedMedia; refReference::_Lreference ]
End If
#
December 29, ଘ౮27 21:39:20 Library.fp7 - selectRefMediaForLearnRecord -1-
