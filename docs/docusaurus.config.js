// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion

const lightCodeTheme = require('prism-react-renderer/themes/github');
const darkCodeTheme = require('prism-react-renderer/themes/dracula');

/** @type {import('@docusaurus/types').Config} */
const config = {
  title : 'Graaf lib',
  tagline : 'A general-purpose lightweight graph library implemented in C++',
  favicon : 'img/favicon.ico',

  // Set the production url of your site here
  url : 'https://bobluppes.github.io/',
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl : '/graaf/',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName : 'bobluppes',  // Usually your GitHub org/user name.
  projectName : 'graaf',           // Usually your repo name.

  trailingSlash : false,

  onBrokenLinks : 'throw',
  onBrokenMarkdownLinks : 'warn',

  // Even if you don't use internalization, you can use this field to set useful
  // metadata like html lang. For example, if your site is Chinese, you may want
  // to replace "en" with "zh-Hans".
  i18n : {
    defaultLocale : 'en',
    locales : ['en'],
  },

  presets : [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs : {
          sidebarPath : require.resolve('./sidebars.js'),
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl : 'https://github.com/bobluppes/graaf/tree/main/',
        },
        theme : {
          customCss : require.resolve('./src/css/custom.css'),
        },
      }),
    ],
  ],

  themeConfig :
      /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
      ({
        // Replace with your project's social card
        image : 'img/docusaurus-social-card.jpg',
        navbar : {
          title : 'Graaf lib',
          logo : {
            alt : 'Graaf Logo',
            src : 'img/graaf.png',
          },
          items : [
            {
              type : 'docSidebar',
              sidebarId : 'quickstartSidebar',
              position : 'left',
              label : 'Quickstart',
            },
            {
              type : 'docSidebar',
              sidebarId : 'algorithmSidebar',
              position : 'left',
              label : 'Algorithms',
            },
            {
              type : 'docSidebar',
              sidebarId : 'exampleSidebar',
              position : 'left',
              label : 'Examples',
            },
            {
              href : 'https://github.com/bobluppes/graaf',
              label : 'GitHub',
              position : 'right',
            },
          ],
        },
        footer : {
          style : 'dark',
          links : [
            {
              title : 'Docs',
              items : [
                {
                  label : 'Quickstart',
                  to : '/docs/quickstart/intro',
                },
                {
                  label : 'Algorithms',
                  to : '/docs/algorithms/intro',
                },
                {
                  label : 'Examples',
                  to : '/docs/examples/intro',
                },
              ],
            },
            {
              title : 'Community',
              items : [
                {
                  label : 'Discord',
                  href : 'https://discord.gg/cGczwRHJ9K',
                },
                {
                  label : 'Twitter',
                  href : 'https://twitter.com/graaflib',
                },
              ],
            },
            {
              title : 'More',
              items : [
                {
                  label : 'GitHub',
                  href : 'https://github.com/bobluppes/graaf',
                },
              ],
            },
          ],
          copyright : `Copyright © ${new Date().getFullYear()} Graaf,
          Inc.Built with Docusaurus.`,
        },
        prism : {
          theme : lightCodeTheme,
          darkTheme : darkCodeTheme,
        },
      }),
};

module.exports = config;
