stock LoadStaticLootsFromFile(const filename[])
{
    new
        line[55],
        File:file_ptr,
        Float:spawnX,
        Float:spawnY,
        Float:spawnZ,
        lootsLoaded
    ;

    file_ptr = fopen(filename, filemode:io_read);

    if (!file_ptr) return 0;
    lootsLoaded = 0;

    while(fread(file_ptr, line, sizeof line) > 0)
    {
        sscanf(line, "p<,>fff", spawnX, spawnY, spawnZ);

        CreateRandomLootItem(spawnX, spawnY, spawnZ);
        lootsLoaded++;
    }
    fclose(file_ptr);
    printf("Loaded file %s with %d loots", filename, lootsLoaded);
    return lootsLoaded;
}

stock ConvertStaticLootsFile(const destfile[], Float:x, Float:y, Float:z)
{
    new
        File:handle,
        tmpString[152]
    ;

    handle = fopen(destfile, filemode:io_write);

    if(!handle) {
        printf("Can't find file %s", destfile);
        fclose(handle);
        return 0;
    }
    format(tmpString, sizeof(tmpString), "CreateRandomLootItem(%f, %f, %f);\n", x, y, z);
    fwrite(handle, tmpString);
    fclose(handle);
    return 1;
}

stock ConvertFile(const filename[], const destfile[])
{
    new
        line[55],
        File:fromFile,
        File:toFile,
        tmpString[152],
        Float:pos[3],
        totalConverted
    ;
    fromFile = fopen(filename, filemode:io_read);
    toFile = fopen(destfile, filemode:io_write);

    if(!fromFile || !toFile) return 0;
    totalConverted = 0;
    
    while(fread(fromFile, line, sizeof line) > 0)
    {
        sscanf(line, "p<,>fff", pos[0], pos[1], pos[2]);
        format(tmpString, sizeof(tmpString), "CreateRandomLootItem(%f, %f, %f);\n", pos[0], pos[1], pos[2]);
        fwrite(toFile, tmpString);
        totalConverted++;
    }
    fclose(fromFile);
    fclose(toFile);
    printf("Total converted files %d", totalConverted);
    return totalConverted;
}