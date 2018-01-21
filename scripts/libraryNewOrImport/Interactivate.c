January 10, 2018 16:33:46 Library.fmp12 - Interactivate -1-
libraryNewOrImport: Interactivate
#
#
#
#This script forces the creation of new picture
#thumbnails whose size is determined in the
#pictureThumbnail field calculation. If you
#change it, then you need to run this script to
#see the new sized thumbnails.
#
#Source: http://www.teamdf.com/weetbicks/252/change-containers-from-files-to-interactive-content-in-an-instant
#
#!!!IMPORTANT!!!
#Custom function required.
#Function Name: Interactivate
#Parameters: _container
#Interactivate ( _container ) = Case ( _container ≠ "" ; Case ( _container ≠ "Replace Me. Media Required" ;
 Base64Decode ( Base64Encode ( _container ) ; GetContainerAttribute ( _container ; "FileName" ) ) ;
 "Replace Me. Media Required" ) )
#
#
Set Variable [ $$stoploadCitation; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Update reference picture thumbnails.
Go to Layout [ “Reference” (reference) ]
Replace Field Contents [ reference::pictureThumbnail; Replace with calculation: Interactivate ( reference::picture ) ]
[ No dialog ]
#
#Update testlearn picture thumbnails.
Go to Layout [ “learn1” (testlearn) ]
Replace Field Contents [ testlearn::picture; Replace with calculation: Interactivate ( testlearn::picture ) ]
[ No dialog ]
#
Set Variable [ $$stoploadCitation ]
Close Window [ Current Window ]
#
#
