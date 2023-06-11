    /**
     * parse the result to the HTML required to render it
     * @param result object of format {title, path, content} which describes a page on the site
     */
    result_to_html(result) {
        //create title and path
        let title = result.title;
        let path = base_url.slice(0, -1) + result.path;
        if (path.endsWith("/index.html")) {
            path = path.slice(0, -11);
        }
        // create preview html
        let preview = result.content;
        
        // Find a position where the search words occur near each other
        let positions = []

        this.current_query.words.forEach(function(searchword) {
            let currMatches;
            while((currMatches = searchword.regex.exec(preview)) !== null) {
                positions.push({
                    index: searchword.regex.lastIndex,
                    word: searchword.word
                });
            }
        })



        
        positions.sort(function(a,b) { return a.index - b.index });
        //are two sets equal
        function setsEqual(s1, s2) {
            if (s1.size !== s2.size) return false;
            for (var a of s1) if (!s2.has(a)) return false;
            return true;
        }
        let allWords = new Set(this.current_query.words.map(function(word) { return word.word }))
        
        let pos = 0;
        let best = {
            min: 0,
            max: 0,
            totalDist: Infinity, //distance between words
            totalFound: 0 //total number of words found
        };
        for (let i = 0; i < positions.length; i++) {
            const position = positions[i];
            let word = position.word;
            let index = position.index;

            // find out how far we have to go from this position to find all words
            let foundWords = new Set();
            foundWords.add(position.word);

            let totalDist = 0; //total distance between words for this combination
            let max = index; //leftmost word find
            let min = index //rightmost word find

            if (setsEqual(allWords, foundWords)) {
                //1 word search
                best.min = index + 10;
                best.max = index - 10
                break;
            } else {
                // search around this word
                for (let j = 0; i + j < positions.length || i - j > 0; j++) {
                    // search j ahead
                    let exceeded = 0;
                    if (i + j < positions.length - 1) {
                        let ahead = positions[i + j];
                        let dist = ahead.index - index;
                        if (dist > buffer) { //exceeded buffer
                            exceeded++;
                        } else if (!foundWords.has(ahead.word)) { // found a word
                            foundWords.add(ahead.word);
                            max = ahead.index;
                            totalDist += ahead.index - index
                        }
                    }
                    //search j behind
                    if (i - j >= 0) {
                        let behind = positions[i - j];
                        let dist = index - behind.index;
                        if (dist > buffer) { //exceeded buffer
                            exceeded++;
                        } else if (!foundWords.has(behind.word)) { // found a word
                            foundWords.add(behind.word);
                            min = behind.index;
                            totalDist += index - behind.index;
                        }
                    }
                    if (setsEqual(allWords, foundWords) || exceeded == 2) { //found all the words in proximity, or both searches exceeded the buffer
                        break;
                    }
                }
            }
            //by now we must have found as many words as we can
            //total found words takes priority over the distance
            if (foundWords.size > best.totalFound || (totalDist < best.totalDist && foundWords.size >= best.totalFound)) {
                // new best
                best.totalDist = totalDist;
                best.max = max;
                best.min = min;
                best.totalFound = foundWords.size;
            }
        }
        
        // buffer around keyword
        let left = Math.max(0, best.min - buffer);
        let right = Math.min(preview.length, best.max + buffer);
        preview = preview.slice(left, right); //extract buffer

        // add elipses to preview so people know that the preview is not the complete page data
        if (right < result.content.length) preview += "&hellip;";
        if (left > 0) preview = "&hellip; " + preview;

        // surround preview keywords with highlight class span tags
        preview = preview.replace(this.current_query.joined, "<span class='search-word-found'>$1</span>");
        // surround title keywords with highlight class span tags
        title = title.replace(this.current_query.joined, "<span class='search-word-found'>$1</span>");

        // result html template
        return `
            <div class="search-result mb-4">
                <div class="title">
                    <a href="${path}">${title}</a>
                </div>
                <div class="preview">
                    ${preview}
                </div>
            </div>
        `; //end template
    }
