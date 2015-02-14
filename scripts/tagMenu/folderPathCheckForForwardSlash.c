tagMenu: folderPathCheckForForwardSlash
If [ Right ( tagMenus::tag ; 1 ) ≠ "/" and $$citationMatch = "folderPath" ]
Show Custom Dialog [ Message: "All filepaths must end with forward slash /. Make sure you did not copy the file name along with the file path."; Buttons: “OK” ]
End If
January 7, 平成26 16:35:30 Imagination Quality Management.fp7 - folderPathCheckForForwardSlash -1-
