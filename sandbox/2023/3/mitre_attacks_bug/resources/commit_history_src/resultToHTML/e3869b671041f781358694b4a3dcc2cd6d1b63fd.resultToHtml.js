/**
   * Converts a search result object to an HTML string with highlighted search words.
   * The HTML string will include the result's title, a link to the result's path, and a preview of the content
   * with search words highlighted. The preview will be trimmed to a buffer size around the found words.
   *
   * @private
   * @function
   * @param {Object} result - A search result object containing an `id`, a `title`, a `path`, and a `content` property.
   * @returns {string} An HTML string representing the search result with highlighted search words.
   */
  #resultToHTML(result) {
    // create title and path
    let { title } = result;

    let path = base_url.slice(0, -1) + result.path;

    if (path.endsWith('/index.html')) {
      path = path.slice(0, -11);
    }

    // create preview html
    let preview = result.content;

    // Find a position where the search words occur near each other
    const positions = [];

    this.currentQuery.words.forEach((searchWord) => {
      let currMatches;
      while ((currMatches = searchWord.regex.exec(preview)) !== null) {
        positions.push({
          index: searchWord.regex.lastIndex,
          word: searchWord.word,
        });
      }
    });

    positions.sort((a, b) => a.index - b.index);

    // are two sets equal
    function setsEqual(s1, s2) {
      if (s1.size !== s2.size) return false;
      for (const a of s1) if (!s2.has(a)) return false;
      return true;
    }

    const allWords = new Set(this.currentQuery.words.map((word) => word.word));

    const pos = 0;
    const best = {
      min: 0,
      max: 0,
      totalDist: Infinity, // distance between words
      totalFound: 0, // total number of words found
    };
    for (let i = 0; i < positions.length; i++) {
      const position = positions[i];
      const {word} = position;
      const {index} = position;

      // find out how far we have to go from this position to find all words
      const foundWords = new Set();
      foundWords.add(position.word);

      let totalDist = 0; // total distance between words for this combination
      let max = index; // leftmost word find
      let min = index; // rightmost word find

      if (setsEqual(allWords, foundWords)) {
        // 1 word search
        best.min = index + 10;
        best.max = index - 10;
        break;
      } else {
        // search around this word
        for (let j = 0; i + j < positions.length || i - j > 0; j++) {
          // search j ahead
          let exceeded = 0;
          if (i + j < positions.length - 1) {
            const ahead = positions[i + j];
            const dist = ahead.index - index;
            if (dist > this.buffer) { // exceeded buffer
              exceeded++;
            } else if (!foundWords.has(ahead.word)) { // found a word
              foundWords.add(ahead.word);
              max = ahead.index;
              totalDist += ahead.index - index;
            }
          }
          // search j behind
          if (i - j >= 0) {
            const behind = positions[i - j];
            const dist = index - behind.index;
            if (dist > this.buffer) { // exceeded buffer
              exceeded++;
            } else if (!foundWords.has(behind.word)) { // found a word
              foundWords.add(behind.word);
              min = behind.index;
              totalDist += index - behind.index;
            }
          }
          // found all the words in proximity, or both searches
          if (setsEqual(allWords, foundWords) || exceeded == 2) {
            // exceeded the buffer
            break;
          }
        }
      }
      // by now we must have found as many words as we can
      // total found words takes priority over the distance
      if (foundWords.size > best.totalFound || (totalDist < best.totalDist
          && foundWords.size >= best.totalFound)) {
        // new best
        best.totalDist = totalDist;
        best.max = max;
        best.min = min;
        best.totalFound = foundWords.size;
      }
    }

    // buffer around keyword
    const left = Math.max(0, best.min - this.buffer);
    const right = Math.min(preview.length, best.max + this.buffer);
    preview = preview.slice(left, right); // extract buffer

    // add ellipses to preview so people know that the preview is not the complete page data
    if (right < result.content.length) preview += '&hellip;';
    if (left > 0) preview = `&hellip; ${preview}`;

    // surround preview keywords with highlight class span tags
    preview = preview.replace(this.currentQuery.joined, "<span class='search-word-found'>$1</span>");
    // surround title keywords with highlight class span tags
    title = title.replace(this.currentQuery.joined, "<span class='search-word-found'>$1</span>");

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
        `; // end template
  }
