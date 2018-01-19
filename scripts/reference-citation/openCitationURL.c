January 18, 2018 15:52:08 Library.fmp12 - openReferenceWebsite -1-
reference: openReferenceWebsite
#
#
#Note that user has clicked the web button.
Set Variable [ $$openReferencedWebsite; Value:1 ]
#
#
#Perform the showFileWebsite script to see if
#there is a website to show, and if there is
#open it.
Perform Script [ “showReferencedFileFolderOrWebsite” ]
#
#
