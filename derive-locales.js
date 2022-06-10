// To run, use `deno run --allow-read derive-locales.js <path/to/i18nlangtag/source/isolang/isolang.cxx>`
// https://deno.land to get deno.

const [filename] = Deno.args

const cxx = (await Deno.readTextFile(filename)).split("\n")
const locales = {}

for (const line of cxx) {
    const result = /\{\s*(.*),\s*"(.*)",\s*"(.*)",\s*(.*)\s*\}/.exec(line)
    if (result == null) {
        continue
    }
    if (result[2] === "") {
        continue
    }

    const lang = result[2]
    const country = result[3]

    if (locales[lang] == null) {
        locales[lang] = []
    }

    if (country !== "") {
        locales[lang].push(country)
    }
}

console.log(JSON.stringify(locales, null, 2))