pictures: showRefURLmedia
#
#Inform user if they have not enter a URL.
If [ reference::URL = "" and reference::showMedia ≠ "" ]
Show Custom Dialog [ Message: "Enter a valid URL below (web address) to see webmedia displayed here."; Buttons: “OK” ]
End If
If [ reference::picture ≠ "" and reference::showMedia ≠ "" ]
Show Custom Dialog [ Message: "Click on the picture and delete it to see your webmedia."; Buttons: “OK” ]
End If
Go to Field [ ]
December 27, ଘ౮27 19:48:49 Library.fp7 - showRefURLmedia -1-
