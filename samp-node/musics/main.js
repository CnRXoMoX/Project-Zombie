const Discord = require('discord.js');
const bot = new Discord.Client({ partials: ["MESSAGE", "CHANNEL", "REACTION"]});
const { prefix, token} = require('./config.json');
const fs = require('fs');
bot.acommands = new Discord.Collection();
bot.commands = new Discord.Collection();

const commandFiles = fs.readdirSync('./commands').filter(file => file.endsWith('.js'));
const acommandFiles = fs.readdirSync('./acommands').filter(file => file.endsWith('.js'));

samp.on(EVENT_GAME_MODE_INIT, () => {
    samp.callNative('print', 's', "samp-node working!");
    bot.login(token);
})

for (const file of commandFiles) {
    const commands = require(`./commands/${file}`);
    bot.commands.set(command.name, command);
}

for (const file of acommandFiles) {
    const acommands = require(`./acommands/${file}`);
    bot.acommands.set(command.name, command);
}

bot.on('ready', () => {
    samp.callNative('print', 's', "Bot is now ready!");
    console.log('Bot is now ready!');
})

bot.on('disconnect', () => {
    console.log('Bot is now disconnected');
})

bot.on('message', message => {
    if (!message.content.startsWith(prefix) || message.author.bot) return;
    if (message.channel.type === 'dm') return;
    if (!message.member.hasPermission("MANAGE_MESSAGES")) return;

    const args = message.content.slice(prefix.length).trim().split(' ');
    const acommandName = args.shift().toLowerCase();

    if (!bot.acommands.has(acommandName)) return;

    const acommand = bot.acommands.get(acommandName) 
        || bot.acommand.find(acmd => acmd.aliases && acmd.aliases.includes(acommandName));

    if (!acommand) return;

    if (acommand.args && !args.length) {
        let reply = `You didn't provided any aruments, <@${message.author.id}>`;

        if(acommand.usage) {
            reply += `\nUSAGE: \`${prefix}${acommand.name} ${acommand.usage}\``;
        }
        return message.channel.send(reply);
    }

    if (acommand.guildOnly && message.channel.type === 'dm') {
        return message.channel.send('I can\'t execute that in DMS');
    }

    if (!cooldown.has(acommand.name)) {
        cooldown.set(acommand.name, new Discord.Collection());
    }

    const now = Date.now();
    const timestamps = cooldown.get(acommand.name);
    const cooldownAmount = (acommand.cooldown || 3) * 1000;

    if (timestamps.has(message.author.id)) {
        const expirationTime = timestamps.get(message.author.id) + cooldownAmount;

        if (now < expirationTime) {
            const timeLeft = (expirationTime - now) / 1000;
            return message.reply(`please wait ${timeLeft.toFixed(1)} more second(s) before reusing the \`${acommand.name}\` command`);
        }
    }

    try{
        var cmdChanLogs = message.guild.channels.cache.find(c => c.name === "discord-admin-command-logs");
        acommand.execute(message, args);
        var log = new Discord.MessageEmbed()
            .setTitle('Admin Command USED!')
            .setAuthor(message.author.username)
            .addField('Command:', acommand.name)
            .addField('Parameters:', args)
            cmdChanLogs.send(log);
    } catch (error) {
        console.error(error);
        message.reply('there was an error trying to execute that command!');
    }
})

bot.on('message', message => {
    if (!message.content.startsWith(prefix) || message.author.bot) return;
    if (message.channel.type === 'dm') return;

    const args = message.content.slice(prefix.length).trim().split(' ');
    const commandName = args.shift().toLowerCase();

    if (!bot.commands.has(commandName)) return;

    const commands = bot.commands.get(commandName) 
        || bot.commands.find(acmd => acmd.aliases && acmd.aliases.includes(commandName));

    if (!command) return;

    if (command.args && !args.length) {
        let reply = `You didn't provided any aruments, <@${message.author.id}>`;

        if(command.usage) {
            reply += `\nUSAGE: \`${prefix}${command.name} ${command.usage}\``;
        }
        return message.channel.send(reply);
    }

    if (command.guildOnly && message.channel.type === 'dm') {
        return message.channel.send('I can\'t execute that in DMS');
    }

    if (!cooldown.has(command.name)) {
        cooldown.set(command.name, new Discord.Collection());
    }

    const now = Date.now();
    const timestamps = cooldown.get(command.name);
    const cooldownAmount = (command.cooldown || 3) * 1000;

    if (timestamps.has(message.author.id)) {
        const expirationTime = timestamps.get(message.author.id) + cooldownAmount;

        if (now < expirationTime) {
            const timeLeft = (expirationTime - now) / 1000;
            return message.reply(`please wait ${timeLeft.toFixed(1)} more second(s) before reusing the \`${command.name}\` command`);
        }
    }
    
    try{
        command.execute(message, args);
    } catch (error) {
        console.error(error);
        message.reply('there was an error trying to execute that command!');
    }
})