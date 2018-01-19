January 18, 2018 15:37:00 Library.fmp12 - showTagLink1 -1-
reference: showTagLink1
#
#Capture needed link info.
Set Variable [ $$tagMenusRealCheckbox; Value:tagFileLocation1::kfileORkTestItemCreatorNode ]
Set Variable [ $$tagMenusFilePath; Value:tagFileLocation1::tag ]
Set Variable [ $$tagMenusFileName; Value:refTitle1::fileName ]
Set Variable [ $$tagMenusFileLocation; Value:refTitle1::kfileLocation ]
Set Variable [ $$tagMenusURL; Value:refTitle1::URL ]
Set Variable [ $$tagMenusISBN; Value:refTitle1::ISBN ]
Set Variable [ $$tagMenusISSN; Value:refTitle1::ISSN ]
Set Variable [ $$tagMenusDOI; Value:refTitle1::DOI ]
#
#Open link for user.
Perform Script [ “showReferencedFileFolderOrWebsite (update and name showFileInTagandLearnWindows)” ]
#
#Clear link variables.
Set Variable [ $$tagMenusRealCheckbox ]
Set Variable [ $$tagMenusFilePath ]
Set Variable [ $$tagMenusFileName ]
Set Variable [ $$tagMenusFileLocation ]
Set Variable [ $$tagMenusURL ]
Set Variable [ $$tagMenusISBN ]
Set Variable [ $$tagMenusISSN ]
Set Variable [ $$tagMenusDOI ]
#
