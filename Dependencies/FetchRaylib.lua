function download_progress(total, current)
    local ratio = current / total;
    ratio = math.min(math.max(ratio, 0), 1);
    local percent = math.floor(ratio * 100);
    print("Download progress (" .. percent .. "%/100%)")
end

if (not os.isfile("raylib-master.zip")) then
    print("[-] Raylib not found, fetching master from Github!")

    local result_str, response_code = http.download(
        "https://github.com/raysan5/raylib/archive/refs/heads/master.zip", 
        "raylib-master.zip",
        {
            progress = download_progress,
            headers = { "From: Premake", "Referer: Premake" }
        }
    )

    zip.extract("raylib-master.zip", "../Dependencies")
    os.remove("raylib-master.zip")

    print("[+] Raylib unpacked and ready to use!")
end