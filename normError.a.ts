// error in json format 
function normalizeError(errno : unknown): Error{
    if ( errno  instanceof Error) return errno;
    try{
      const ErrAsJson = JSON.stringify(errno,null,2);
      return new Error(ErrAsJson ?? String(errno));
    }catch{
        return new Error(String(errno));
    }
}
