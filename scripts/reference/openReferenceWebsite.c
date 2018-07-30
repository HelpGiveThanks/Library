July 30, 2018 16:34:00 Library.fmp12 - openReferenceWebsite -1-
reference: openReferenceWebsite
#
#
#Open copyright's website if user is on the
#copyright tag menu.
If [ refTitle1::URL ≠ "" and $$citationMatch = "copyright" ]
Open URL [ refTitle1::URL ]
[ No dialog ]
Exit Script [ ]
End If
#
#
#Note that user has clicked the web button.
Set Variable [ $$openReferencedWebsite; Value:1 ]
#
#
#Perform the showFileWebsite script to see if
#there is a website to show, and if there is
#open it.
Perform Script [ “showReferencedFileFolder” ]
#
#
